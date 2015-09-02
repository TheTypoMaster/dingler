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

#ifndef IMAGE_EXPRESSION_INFRASTRUCTURE_ELEMENTARY_CONST_EXPRESSIONS_H_
#define IMAGE_EXPRESSION_INFRASTRUCTURE_ELEMENTARY_CONST_EXPRESSIONS_H_

#include <string>
namespace image {using std::string; }

#include "base/strings/stringprintf.h"
#include "image/query/base/types_infrastructure.h"
#include "image/query/base/tuple_schema.h"
#include "image/query/expression/expression.h"
#include "image/query/expression/basic_bound_expression.h"
#include "image/query/expression/elementary_bound_const_expressions.h"

namespace image {

template <DataType type,
          bool is_variable_length = TypeTraits<type>::is_variable_length>
class ConstExpression: public Expression {
 public:
  typedef typename TypeTraits<type>::cpp_type cpp_type;
  explicit ConstExpression(const cpp_type& value)
      : value_(value) {}

  virtual FailureOrOwned<BoundExpression> DoBind(
      const TupleSchema& input_schema,
      BufferAllocator* allocator,
      rowcount_t max_row_count) const {
    return InitBasicExpression(
        max_row_count,
        new BoundConstExpression<type>(allocator, value_),
        allocator);
  }

  virtual string ToString(bool verbose) const {
    string result_description;
    if (verbose)
      result_description = base::StringPrintf("<%s>", TypeTraits<type>::name());
    else
      result_description = "";

    PrintTyped<type>(value_, &result_description);
    return result_description;
  }

 private:
  const cpp_type value_;
};

// Partial specialization for variable-length types (STRING and BINARY)
template <DataType type>
class ConstExpression<type, true>: public Expression {
 public:
  typedef typename TypeTraits<type>::cpp_type cpp_type;  // StringPiece
  explicit ConstExpression(const cpp_type& value)
      : value_(value.data(), value.size()) {}

  virtual FailureOrOwned<BoundExpression> DoBind(
      const TupleSchema& input_schema,
      BufferAllocator* allocator,
      rowcount_t max_row_count) const {
    return InitBasicExpression(
        max_row_count,
        new BoundConstExpression<type>(allocator, StringPiece(value_)),
        allocator);
  }

  virtual string ToString(bool verbose) const {
    string prefix = "";
    if (verbose)
      prefix = type == STRING ? "<STRING>" : "<BINARY>";

    return base::StringPrintf("%s'%s'", prefix.c_str(), value_.c_str());
  }

 private:
  // Holds a copy of input data.
  const string value_;
};

}  // namespace image

#endif  // IMAGE_EXPRESSION_INFRASTRUCTURE_ELEMENTARY_CONST_EXPRESSIONS_H_
