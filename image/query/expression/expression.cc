// Copyright 2010 Google Inc.  All Rights Reserved
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

#include "image/query/expression/expression.h"

#include <algorithm>
//#include "image/query/utils/std_namespace.h"

#include "base/memory/scoped_ptr.h"
#include "image/query/utils/failureor.h"
#include "image/query/base/exception.h"
#include "image/query/base/exception_macros.h"
#include "image/query/utils/supersonic.pb.h"
#include "image/query/utils/strings/join.h"

namespace image {
class BufferAllocator;

// ----------------- BoundExpression -------------------------------------------

std::set<string> BoundExpression::referred_attribute_names() const {
  std::set<string> attributes_names;
  CollectReferredAttributeNames(&attributes_names);
  return attributes_names;
}

// ----------------- BoundExpressionTree ---------------------------------------

FailureOrVoid BoundExpressionTree::Init(BufferAllocator* allocator,
                                        rowcount_t max_row_count) {
  PROPAGATE_ON_FAILURE(skip_vector_storage_.TryReallocate(max_row_count));
  return common::Success();
}

FailureOrOwned<BoundExpressionTree>
    CreateBoundExpressionTree(BoundExpression* expression,
                              BufferAllocator* allocator,
                              rowcount_t max_row_count) {
  scoped_ptr<BoundExpressionTree> expression_tree(
      new BoundExpressionTree(expression, allocator));
  PROPAGATE_ON_FAILURE(expression_tree->Init(allocator, max_row_count));
  return common::Success(expression_tree.release());
}

EvaluationResult BoundExpressionTree::Evaluate(const View& input) {
  if (row_capacity() < input.row_count()) {
    THROW(new Exception(
        ERROR_TOO_MANY_ROWS,
        StrCat("Trying to evaluate expression: ",
               result_schema().GetHumanReadableSpecification(),
               " with number of rows: ", input.row_count(),
               ", while the expression has capacity for less rows: ",
               row_capacity())));
  }
  // Fill the skip_vector with falses - evaluate everything.
  for (int i = 0; i < skip_vector_storage_.column_count(); ++i) {
    bit_pointer::FillWithFalse(skip_vector_storage_.view().column(i),
                               input.row_count());
  }
  EvaluationResult result =
      root_->DoEvaluate(input, skip_vector_storage_.view());
  PROPAGATE_ON_FAILURE(result);
  return result;
}

rowcount_t BoundExpressionTree::row_capacity() const {
  return std::min(skip_vector_storage_.row_capacity(), root_->row_capacity());
}

// ------------------ Expression -----------------------------------------------

FailureOrOwned<BoundExpressionTree> Expression::Bind(
    const TupleSchema& input_schema,
    BufferAllocator* allocator,
    rowcount_t max_row_count) const {
  FailureOrOwned<BoundExpression> bound_root = DoBind(input_schema, allocator,
                                                      max_row_count);
  PROPAGATE_ON_FAILURE(bound_root);
  return CreateBoundExpressionTree(bound_root.release(),
                                   allocator,
                                   max_row_count);
}

// -------------------- Lists --------------------------------------------------

FailureOrOwned<BoundExpressionList> ExpressionList::DoBind(
    const TupleSchema& input_schema,
    BufferAllocator* allocator,
    rowcount_t max_row_count) const {
  scoped_ptr<BoundExpressionList> bound_list(new BoundExpressionList());
  for (int i = 0; i < expressions_.size(); ++i) {
    FailureOrOwned<BoundExpression> result =
        expressions_[i]->DoBind(input_schema, allocator, max_row_count);
    PROPAGATE_ON_FAILURE(result);
    bound_list->add(result.release());
  }
  return common::Success(bound_list.release());
}

const string BoundExpressionList::ToString(bool verbose) const {
  string result_description;
  for (vector<linked_ptr<BoundExpression> >::const_iterator it =
      expressions_.begin(); it < expressions_.end(); ++it) {
    if (it != expressions_.begin()) result_description.append(", ");
    // The next for lines could be replaced by GetMultiExpressionName, but I
    // want to avoid a dependency on expression_utils.
    const TupleSchema& subexpression_schema = it->get()->result_schema();
    for (int i = 0; i < subexpression_schema.attribute_count(); ++i) {
      result_description.append(subexpression_schema.attribute(i).name());
    }
  }
  return result_description;
}

void BoundExpressionList::CollectReferredAttributeNames(
    std::set<string>* referred_attribute_names) const {
  for (vector<linked_ptr<BoundExpression> >::const_iterator it =
      expressions_.begin(); it < expressions_.end(); ++it) {
    (*it)->CollectReferredAttributeNames(referred_attribute_names);
  }
}

const string ExpressionList::ToString(bool verbose) const {
  string result_description;
  for (vector<linked_ptr<const Expression> >::const_iterator it =
      expressions_.begin(); it < expressions_.end(); ++it) {
    if (it != expressions_.begin()) result_description.append(", ");
    result_description.append((*it)->ToString(verbose));
  }
  return result_description;
}

}  // namespace image
