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

#include "image/query/cursor/lookup_index.h"

#include "image/query/base/projector.h"
#include "image/query/base/tuple_schema.h"

namespace image {

BoundSingleSourceProjector LookupIndex::value_selector() const {
  const TupleSchema& source_schema = key_selector().source_schema();
  BoundSingleSourceProjector result(source_schema);
  for (int i = 0; i < source_schema.attribute_count(); i++) {
    if (!key_selector().IsAttributeProjected(i))
      result.Add(i);
  }
  return result;
}

}  // namespace image
