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

#include "image/query/cursor/ordering.h"

#include <memory>
#include <string>

#include "base/strings/stringprintf.h"
#include "base/memory/scoped_ptr.h"
#include "image/query/utils/failureor.h"
#include "image/query/base/exception.h"
#include "image/query/base/exception_macros.h"
#include "image/query/base/projector.h"

namespace image {

FailureOrOwned<const BoundSortOrder> SortOrder::Bind(
    const TupleSchema& source_schema) const {
  std::unique_ptr<BoundSingleSourceProjector> projector(
      new BoundSingleSourceProjector(source_schema));
  vector<ColumnOrder> column_order;
  for (size_t i = 0; i < projectors_.size(); ++i) {
    FailureOrOwned<const BoundSingleSourceProjector> component =
        projectors_[i]->Bind(source_schema);
    PROPAGATE_ON_FAILURE(component);
    for (size_t j = 0; j < component->result_schema().attribute_count();
         ++j) {
      if (!projector->AddAs(
              component->source_attribute_position(j),
              component->result_schema().attribute(j).name())) {
        THROW(new Exception(
            ERROR_ATTRIBUTE_EXISTS,
            base::StringPrintf(
                "Duplicate attribute name \"%s\" in result schema (%s)",
                component->result_schema().attribute(j).name().c_str(),
                component->result_schema().
                    GetHumanReadableSpecification().c_str())));
      }
      column_order.push_back(column_order_[i]);
    }
  }
  return common::Success(new BoundSortOrder(projector.release(), column_order));
}

}  // namespace image
