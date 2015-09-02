// Copyright 2010 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include "image/query/cursor/aggregator.h"

#include <stddef.h>

#include <memory>
#include <string>

#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/stringprintf.h"
#include "image/query/utils/failureor.h"
#include "image/query/base/exception.h"
#include "image/query/base/exception_macros.h"
#include "image/query/cursor/aggregate.h"
#include "image/query/utils/supersonic.pb.h"
#include "image/query/utils/strings/join.h"

namespace image {

class BufferAllocator;

FailureOrOwned<Aggregator> Aggregator::Create(
    const AggregationSpecification& aggregation_specification,
    const TupleSchema& input_schema,
    BufferAllocator* allocator,
    rowcount_t result_initial_row_capacity) {
  std::unique_ptr<Aggregator> aggregator(new Aggregator());
  PROPAGATE_ON_FAILURE(aggregator->Init(
      aggregation_specification, input_schema, allocator,
      result_initial_row_capacity));
  return common::Success(aggregator.release());
}

bool Aggregator::Reallocate(rowcount_t new_capacity) {
  rowcount_t old_capacity = capacity();
  bool success = data_->Reallocate(new_capacity);
  // Rebind even if the realloc failed, as it might have updated some columns.
  std::vector<std::pair<int, linked_ptr<aggregations::ColumnAggregator> > >::iterator
      it;
  for (it = column_aggregator_.begin(); it != column_aggregator_.end(); ++it) {
    it->second->Rebind(old_capacity, data_->row_capacity());
  }
  return success;
}

DataType AggregationOutputType(
    const AggregationSpecification::Element& aggregation,
    const TupleSchema& input_schema,
    int input_position) {
  if (aggregation.output_type_specified()) {
    return aggregation.output_type();
  } else if (aggregation.aggregation_operator() == COUNT) {
    return UINT64;
  } else {
    // The input_position == -1 only for COUNT aggregation so it should
    // have been handled in previous case.
    DCHECK_GE(input_position, 0);
    return input_schema.attribute(input_position).type();
  }
}

// TODO(user): Refactor the aggregation binding process into separate class.
FailureOrOwned<aggregations::ColumnAggregator>
CreateColumnAggregator(
    aggregations::ColumnAggregatorFactory* aggregator_factory,
    const AggregationSpecification::Element& aggregation,
    const TupleSchema& input_schema,
    Block* result_block,
    int result_column_index) {
  if (aggregation.aggregation_operator() == COUNT) {
    if (aggregation.is_distinct()) {
      DataType input_type = input_schema.LookupAttribute(
          aggregation.input()).type();
      return aggregator_factory->CreateDistinctCountAggregator(
          input_type, result_block, result_column_index);
    } else {
      return aggregator_factory->CreateCountAggregator(result_block,
                                                       result_column_index);
    }
  } else {
    DataType input_type = input_schema.LookupAttribute(
        aggregation.input()).type();
    if (aggregation.is_distinct()) {
      return aggregator_factory->CreateDistinctAggregator(
          aggregation.aggregation_operator(),
          input_type,
          result_block,
          result_column_index);
    } else {
      return aggregator_factory->CreateAggregator(
          aggregation.aggregation_operator(),
          input_type,
          result_block,
          result_column_index);
    }
  }
}

FailureOrVoid Aggregator::Init(
    const AggregationSpecification& aggregation_specification,
    const TupleSchema& input_schema,
    BufferAllocator* allocator,
    rowcount_t result_initial_row_capacity) {
  vector<int> input_position_vector;

  // Validate aggregations specifications. Find input_position for each
  // aggregation.
  for (int i = 0; i < aggregation_specification.size(); ++i) {
    const AggregationSpecification::Element& aggregation =
        aggregation_specification.aggregation(i);

    int input_position;
    if (aggregation.aggregation_operator() == COUNT &&
        !aggregation.is_distinct() &&
        aggregation.input().compare("") == 0) {
      input_position = -1;
    } else {
      input_position = input_schema.LookupAttributePosition(
          aggregation.input());
      if (input_position == -1) {
        THROW(new Exception(
            ERROR_ATTRIBUTE_MISSING,
            base::StringPrintf("Incorrect aggregation specification. Aggregation "
                         "input column does not exist: %s.",
                         aggregation.input().c_str())));
      }
    }

    DataType output_type = AggregationOutputType(
        aggregation, input_schema, input_position);

    Nullability result_nullability = NULLABLE;
    if (aggregation.aggregation_operator() == COUNT) {
      result_nullability = NOT_NULLABLE;
    }

    Attribute attribute(
        aggregation.output(), output_type, result_nullability);
    if (!schema_.add_attribute(attribute)) {
      THROW(new Exception(
          ERROR_ATTRIBUTE_EXISTS,
          base::StringPrintf("Incorrect aggregation specification. Aggregation "
                       "output column name is non-unique: '%s'.",
                       aggregation.output().c_str())));
    }
    input_position_vector.push_back(input_position);
  }

  data_.reset(new Block(schema_, allocator));
  if (!data_->Reallocate(result_initial_row_capacity)) {
    THROW(new Exception(
        ERROR_MEMORY_EXCEEDED,
        StrCat("Block allocation failed. Result block with capacity ",
               result_initial_row_capacity, " not allocated.")));
  }

  aggregations::ColumnAggregatorFactory aggregator_factory;

  // After output block is created, column aggregators can be created.
  for (int i = 0; i < aggregation_specification.size(); ++i) {
    FailureOrOwned<aggregations::ColumnAggregator> create_aggregator_result =
        CreateColumnAggregator(&aggregator_factory,
                               aggregation_specification.aggregation(i),
                               input_schema,
                               data_.get(),
                               i);
    PROPAGATE_ON_FAILURE(create_aggregator_result);
    column_aggregator_.push_back(
     std::make_pair(input_position_vector[i],
                  make_linked_ptr(create_aggregator_result.release())));
  }
  return common::Success();
}

inline FailureOrVoid UpdateAggregation(
    int input_position, aggregations::ColumnAggregator* column_aggregator,
    const View& view, const rowid_t result_index_map[]) {
  const Column* input;
  if (input_position != -1) {
    input = &view.column(input_position);
  } else {
    input = NULL;
  }
  return column_aggregator->UpdateAggregation(
      input, view.row_count(), result_index_map);
}


FailureOrVoid Aggregator::UpdateAggregations(const View& view,
                                             const rowid_t result_index_map[]) {
#ifndef NDEBUG
  for (size_t i = 0; i < view.row_count(); ++i) {
    DCHECK_LT(result_index_map[i], data_->view().row_count());
  }
#endif
  std::vector<std::pair<int, linked_ptr<aggregations::ColumnAggregator> > >::iterator it;
  for (it = column_aggregator_.begin(); it != column_aggregator_.end(); ++it) {
    PROPAGATE_ON_FAILURE(UpdateAggregation(it->first,
                                           it->second.get(),
                                           view,
                                           result_index_map));
  }
  return common::Success();
}

void Aggregator::Reset() {
 std::vector<std::pair<int, linked_ptr<aggregations::ColumnAggregator> > >::iterator
      it;
  for (it = column_aggregator_.begin(); it != column_aggregator_.end(); ++it) {
    it->second->Reset();
  }
}

}  // namespace image
