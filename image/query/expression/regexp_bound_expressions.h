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

#ifndef IMAGE_EXPRESSION_CORE_REGEXP_BOUND_EXPRESSIONS_H_
#define IMAGE_EXPRESSION_CORE_REGEXP_BOUND_EXPRESSIONS_H_

#include "image/query/base/result.h"
#include "image/query/base/types.h"
#include "base/strings/string_piece.h"

// For the descriptions of particular functions, see string_expressions.h.
// For the usage of bound expression accessors, see expression.h or kick the
// Supersonic team for documentation.

namespace image {

class BoundExpression;
class BufferAllocator;

FailureOrOwned<BoundExpression> BoundRegexpPartialMatch(
    BoundExpression* str,
    const StringPiece& pattern,
    BufferAllocator* allocator,
    rowcount_t max_row_count);

FailureOrOwned<BoundExpression> BoundRegexpFullMatch(
    BoundExpression* str,
    const StringPiece& pattern,
    BufferAllocator* allocator,
    rowcount_t max_row_count);

FailureOrOwned<BoundExpression> BoundRegexpExtract(
    BoundExpression* str,
    const StringPiece& pattern,
    BufferAllocator* allocator,
    rowcount_t max_row_count);

FailureOrOwned<BoundExpression> BoundRegexpReplace(
    BoundExpression* haystack,
    const StringPiece& pattern,
    BoundExpression* substitute,
    BufferAllocator* allocator,
    rowcount_t max_row_count);

}  // namespace image

#endif  // IMAGE_EXPRESSION_CORE_REGEXP_BOUND_EXPRESSIONS_H_
