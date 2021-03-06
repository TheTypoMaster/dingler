// Copyright 2011 Google Inc. All Rights Reserved.
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
// Author: onufry@google.com (Onufry Wojtaszczyk)
//
// Bound stateful expressions.
// For comments on the semantics see stateful_expressions.h.

#ifndef IMAGE_EXPRESSION_CORE_STATEFUL_BOUND_EXPRESSIONS_H_
#define IMAGE_EXPRESSION_CORE_STATEFUL_BOUND_EXPRESSIONS_H_

#include "image/query/base/result.h"
#include "image/query/base/types.h"

namespace image {

class BoundExpression;
class BufferAllocator;

FailureOrOwned<BoundExpression> BoundChanged(BoundExpression* argument,
                                             BufferAllocator* allocator,
                                             rowcount_t max_row_count);

FailureOrOwned<BoundExpression> BoundRunningSum(BoundExpression* argument,
                                                BufferAllocator* allocator,
                                                rowcount_t max_row_count);

FailureOrOwned<BoundExpression> BoundSmudge(BoundExpression* argument,
                                            BufferAllocator* allocator,
                                            rowcount_t max_row_count);

FailureOrOwned<BoundExpression> BoundRunningMinWithFlush(
    BoundExpression* flush,
    BoundExpression* input,
    BufferAllocator* allocator,
    rowcount_t max_row_count);

FailureOrOwned<BoundExpression> BoundSmudgeIf(BoundExpression* argument,
                                              BoundExpression* condition,
                                              BufferAllocator* allocator,
                                              rowcount_t max_row_count);

}  // namespace image

#endif  // IMAGE_EXPRESSION_CORE_STATEFUL_BOUND_EXPRESSIONS_H_
