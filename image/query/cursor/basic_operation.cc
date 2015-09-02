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

#include "image/query/cursor/basic_operation.h"

#include <string>
#include <typeinfo>

#include "base/logging.h"
#include "image/query/utils/strings/split.h"
#include "image/query/utils/demangle.h"

namespace image {

void BasicOperation::AppendDebugDescription(string* const target) const {
  const size_t size = children_count();
  if (size >= 2) {
    target->append("[");
    for (size_t i = 0; i < size; ++i) {
      if (i > 0) target->append(",");
      child_at(i)->AppendDebugDescription(target);
    }
    target->append("].");
  } else if (size == 1) {
    child()->AppendDebugDescription(target);
    target->append(".");
  }
  target->append(LazilyGetDebugDescription());
}

const string& BasicOperation::LazilyGetDebugDescription() const {
  if (debug_description_.empty()) {
    debug_description_ = DebugDescription();
  }
  return debug_description_;
}

string BasicOperation::DebugDescription() const {
  const string name = Demangle(typeid(*this).name());
  vector<string> split = strings::Split(name, "::");
  CHECK(!split.empty());
  return split.back();
}

}  // namespace image
