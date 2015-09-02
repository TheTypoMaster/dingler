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

#ifndef IMAGE_EXPRESSION_INFRASTRUCTURE_ELEMENTARY_BOUND_CONST_EXPRESSIONS_H_
#define IMAGE_EXPRESSION_INFRASTRUCTURE_ELEMENTARY_BOUND_CONST_EXPRESSIONS_H_

#include <string>

#include "base/strings/stringprintf.h"
#include "image/query/base/tuple_schema.h"
#include "image/query/base/types.h"
#include "image/query/expression/basic_bound_expression.h"

namespace image {

template <DataType type,
          bool is_variable_length = TypeTraits<type>::is_variable_length>
class BoundConstExpression : public BasicBoundConstExpression {
 public:
  typedef typename TypeTraits<type>::cpp_type cpp_type;

  explicit BoundConstExpression(BufferAllocator* const allocator,
                                const cpp_type& value)
      : BasicBoundConstExpression(
            TupleSchema::Singleton(base::StringPrintf("CONST_%s",
                                                TypeTraits<type>::name()),
                                   type, NOT_NULLABLE),
            allocator),
        value_(value) {}

  // Pre-fills data with the value provided.
  virtual FailureOrVoid PostInit() {
    size_t count = my_block()->row_capacity();
    cpp_type* data = my_block()->mutable_column(0)->
        template mutable_typed_data<type>();
    while (count--) {
      *data++ = value_;
    }
    return common::Success();
  }

 private:
  const cpp_type value_;
};

// Partial specialization for variable-length types (STRING and BINARY).
template <DataType type>
class BoundConstExpression<type, true> : public BasicBoundConstExpression {
 public:
  typedef typename TypeTraits<type>::cpp_type cpp_type;

  explicit BoundConstExpression(BufferAllocator* const allocator,
                                const cpp_type& value)
      : BasicBoundConstExpression(
            TupleSchema::Singleton(base::StringPrintf("CONST_%s",
                                                TypeTraits<type>::name()),
                                   type, NOT_NULLABLE),
            allocator),
        string_value_(value.data(), value.size()) {}

  // Pre-fills data with the value provided.
  virtual FailureOrVoid PostInit() {
    StringPiece value(string_value_);
    size_t count = my_block()->row_capacity();
    cpp_type* data = my_block()->mutable_column(0)->
        template mutable_typed_data<type>();
    while (count--) {
      *data++ = value;
    }
    return common::Success();
  }

 private:
  const string string_value_;
};

}  // namespace image

#endif  // IMAGE_EXPRESSION_INFRASTRUCTURE_ELEMENTARY_BOUND_CONST_EXPRESSIONS_H_
