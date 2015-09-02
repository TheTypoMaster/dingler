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
//
// A cursor over the specified number rows with an empty schema.
// Can be used with the Sequence() expression or other terminal expressions
// to create a cursor over hard-coded content.

#ifndef IMAGE_CURSOR_CORE_GENERATE_H_
#define IMAGE_CURSOR_CORE_GENERATE_H_

#include "image/query/base/result.h"
#include "image/query/base/types.h"

namespace image {

// Returns an operation with an empty schema, with 'count' rows.
class Cursor;
class Operation;

Operation* Generate(rowcount_t count);

// Returns an cursor over 'count' rows with an empty schema.
FailureOrOwned<Cursor> BoundGenerate(rowcount_t count);

}  // namespace image

#endif  // IMAGE_CURSOR_CORE_GENERATE_H_
