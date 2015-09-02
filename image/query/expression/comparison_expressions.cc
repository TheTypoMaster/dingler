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
// Author:  onufry@google.com (Onufry Wojtaszczyk)

#include "image/query/expression/comparison_expressions.h"

#include <string>
namespace image {using std::string; }
#include <vector>
using std::vector;

//#include "image/query/utils/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/stringprintf.h"
#include "image/query/base/exception.h"
#include "image/query/base/exception_macros.h"
#include "image/query/base/result.h"
#include "image/query/base/tuple_schema.h"
#include "image/query/base/types.h"
#include "image/query/base/types_infrastructure.h"
#include "image/query/expression/expression.h"
#include "image/query/expression/comparison_bound_expressions.h"
#include "image/query/expression/basic_expressions.h"
#include "image/query/expression/expression_utils.h"
#include "image/query/expression/cast_bound_expression.h"
#include "image/query/utils/supersonic.pb.h"

namespace image {

class BufferAllocator;

namespace {
// The in expression set expression, extending expression. Similar to Concat,
// this doesn't fit into the general scheme of abstract_expressions.h as it has
// an arbitrary number of arguments.
class InExpressionSetExpression : public Expression {
 public:
  InExpressionSetExpression(const Expression* const needle_expression,
                            const ExpressionList* const haystack_arguments)
      : needle_expression_(needle_expression),
        haystack_arguments_(haystack_arguments) {}

 private:
  virtual FailureOrOwned<BoundExpression> DoBind(
      const TupleSchema& input_schema,
      BufferAllocator* allocator,
      rowcount_t max_row_count) const {
    FailureOrOwned<BoundExpression> bound_needle =
        needle_expression_->DoBind(input_schema, allocator, max_row_count);
    PROPAGATE_ON_FAILURE(bound_needle);
    FailureOrOwned<BoundExpressionList> bound_haystack =
        haystack_arguments_->DoBind(input_schema, allocator, max_row_count);
    PROPAGATE_ON_FAILURE(bound_haystack);
    return BoundInSet(bound_needle.release(),
                      bound_haystack.release(),
                      allocator,
                      max_row_count);
  }

  virtual string ToString(bool verbose) const {
    return StrCat(needle_expression_->ToString(verbose),
                  " IN (",
                  haystack_arguments_->ToString(verbose),
                  ")");
  }

  const scoped_ptr<const Expression> needle_expression_;
  const scoped_ptr<const ExpressionList> haystack_arguments_;
};
}  // namespace

const Expression* In(const Expression* const needle_expression,
                     const ExpressionList* haystack_arguments) {
  return new InExpressionSetExpression(needle_expression, haystack_arguments);
}

const Expression* IsOdd(const Expression* const arg) {
  return CreateExpressionForExistingBoundFactory(
      arg, &BoundIsOdd, "IS_ODD($0)");
}

const Expression* IsEven(const Expression* const arg) {
  return CreateExpressionForExistingBoundFactory(
      arg, &BoundIsEven, "IS_EVEN($0)");
}

const Expression* NotEqual(const Expression* const left,
                           const Expression* const right) {
  return CreateExpressionForExistingBoundFactory(
      left, right, &BoundNotEqual, "$0 <> $1");
}

const Expression* Equal(const Expression* const left,
                        const Expression* const right) {
  return CreateExpressionForExistingBoundFactory(
      left, right, &BoundEqual, "$0 == $1");
}

const Expression* Greater(const Expression* const left,
                          const Expression* const right) {
  return CreateExpressionForExistingBoundFactory(
      left, right, &BoundGreater, "$0 > $1");
}

const Expression* GreaterOrEqual(const Expression* const left,
                                 const Expression* const right) {
  return CreateExpressionForExistingBoundFactory(
      left, right, &BoundGreaterOrEqual, "$0 >= $1");
}

const Expression* Less(const Expression* const left,
                       const Expression* const right) {
  return CreateExpressionForExistingBoundFactory(
      left, right, &BoundLess, "$0 < $1");
}

const Expression* LessOrEqual(const Expression* const left,
                              const Expression* const right) {
  return CreateExpressionForExistingBoundFactory(
      left, right, &BoundLessOrEqual, "$0 <= $1");
}
}  // namespace image
