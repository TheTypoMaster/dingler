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
// Defines a number of utility template functions for creation of functions and
// functors depending on DataType.
//
// The idea behind it is to get rid of "by DataType" switches
// and to use common code for comparison of values etc.
//
#ifndef IMAGE_BASE_INFRASTRUCTURE_TYPES_INFRASTRUCTURE_H_
#define IMAGE_BASE_INFRASTRUCTURE_TYPES_INFRASTRUCTURE_H_

#include <stddef.h>
#include <string.h>

#include <algorithm>
//#include "image/query/utils/std_namespace.h"
#include <string>

#include "base/logging.h"
#include "base/strings/string_piece.h"
#include "image/query/base/exception.h"
#include "image/query/base/exception_macros.h"
#include "image/query/base/result.h"
#include "image/query/base/bit_pointers.h"
#include "image/query/base/operators.h"
#include "image/query/base/types.h"
#include "image/query/base/variant_pointer.h"
#include "image/query/base/memory/arena.h"
#include "image/query/utils/supersonic.pb.h"
#include "image/query/utils/strings/join.h"


// ------------------------------------------------------------
// Template for calling single-arg function template parametrized by DataType.
// Assumes that the functor has a templatized, parameter-less operator().
// The functor might be stateful (and an instance may be passed as a parameter).
//
// Example 1.
// Return the sizeof the corresponding C++ type.
//
// struct SizeofResolver {
//   template<DataType type> size_t operator()() const {
//     return TypeTraits<type>::size;
//   }
// };
// size_t size = TypeSpecialization<size_t, SizeOfResolver>(type);
//
//
// Example 2.
// Resolve a function that compares two typed values for inequality.
//
// typedef bool (*LessThanFn)(VariantConstPointer a, VariantConstPointer b);
// template<DataType type>
// bool LessThan(VariantConstPointer a, VariantConstPointer b) {
//   return a == NULL ? b != NULL : b != NULL && a.as<type>() < b.as<type>();
// }
// struct LessThanResolver {
//   template<DataType type>
//   LessThanFn operator()() const { return &LessThan<type>; }
// }
// LessThanFn f = TypeSpecialization<LessThanFn, LessThanResolver>(type);
//
//
// Example 3.
// Resolve a sort function, as above, but also differentiate by nullability.
// Uses a stateful functor.
//
// typedef bool (*LessThanFn)(VariantConstPointer a, VariantConstPointer b);
// template<DataType type, boolean is_nullable>
// bool LessThan(VariantConstPointer a, VariantConstPointer b) {
//   return (is_nullable && a == NULL) ? b != NULL :
//       (!is_nullable || b != NULL) && a.as<type>() < b.as<type>();
// }
// struct LessThanResolver {
//   LessThanResolver(bool is_nullable) : is_nullable(is_nullable) {}
//   template<DataType type> LessThanFn operator()() const {
//     return is_nullable ? Resolve<type, true>() : Resolve<type, false>();
//   }
//   template<DataType type, bool is_nullable_p>
//   LessThanFn Resolve() const { return &LessThan<type, is_nullable_p>; }
//   bool is_nullable;
// }
// LessThanResolver resolver(is_nullable);
// LessThanFn f = TypeSpecialization<LessThanFn, LessThanResolver>(
//     type, resolver);
//
// ------------------------------------------------------------
template<typename ReturnType, typename Functor>
ReturnType TypeSpecialization(const container::DataType type,
                              const Functor functor = Functor()) {
  switch (type) {
  case container::INT32:     return functor.operator()<container::INT32>();
  case container::INT64:     return functor.operator()<container::INT64>();
  case container::UINT32:    return functor.operator()<container::UINT32>();
  case container::UINT64:    return functor.operator()<container::UINT64>();
  case container::FLOAT:     return functor.operator()<container::FLOAT>();
  case container::DOUBLE:    return functor.operator()<container::DOUBLE>();
  case container::BOOL:      return functor.operator()<container::BOOL>();
  case container::DATE:      return functor.operator()<container::DATE>();
  case container::DATETIME:  return functor.operator()<container::DATETIME>();
  case container::STRING:    return functor.operator()<container::STRING>();
  case container::BINARY:    return functor.operator()<container::BINARY>();
  case container::ENUM:      return functor.operator()<container::ENUM>();
  case container::DATA_TYPE: return functor.operator()<container::DATA_TYPE>();
  }
  LOG(FATAL) << "Unknown DataType: " << type;
}

// Specialized TypeSpecialization that only allows the four integer data types
// to be used. ReturnType is assumed to be FailureOr or one of its descendants.
// If it is not, the function will not compile with the THROW macro.
// TODO(user): Add additional specialized versions as necessary. Perhaps,
// NumericTypeSpecialization or DateTypeSpecialization or
// VariableLengthTypeSpecialization.
// TODO(onufry): Note that if the Functor is stateful, and it contains fields
// that should be owned (and are not, due to the fact the functor has to be
// copyable), then a failure resulting from a type mismatch will not cause these
// fields to be released. As such a failure is undistinguishable from other
// failures, you have to assure it will not happen by a runtime check before
// calling this function. I (onufry) think we should instead insist on the
// Functor having a "delete" function (which deletes all owned fields) and call
// it when a type mismatch occurs.
template<typename ReturnType, typename Functor>
ReturnType IntegerTypeSpecialization(
 const container::DataType type, const Functor functor = Functor()) {
  switch (type) {
  case container::INT32:     return functor.operator()<container::INT32>();
  case container::INT64:     return functor.operator()<container::INT64>();
  case container::UINT32:    return functor.operator()<container::UINT32>();
  case container::UINT64:    return functor.operator()<container::UINT64>();
  case container::FLOAT:
  case container::DOUBLE:
  case container::BOOL:
  case container::DATE:
  case container::DATETIME:
  case container::STRING:
  case container::BINARY:
  case container::ENUM:
  case container::DATA_TYPE:
   THROW(new container::Exception(
    container::ERROR_INVALID_ARGUMENT_TYPE,
          StrCat("Non-integer DataType ", DataType_Name(type), " passed to "
                 "IntegerTypeSpecialization.")));
  }
  LOG(FATAL) << "Unknown DataType: " << type;
}

// Specialized TypeSpecialization that only allows numeric data types
// to be used. ReturnType is assumed to be FailureOr or one of its descendants.
// If it is not, the function will not compile with the THROW macro.
// WARNING: may cause memory leaks if Functor contains fields it should own, see
// the todo at IntegerTypeSpecialization.
template<typename ReturnType, typename Functor>
ReturnType NumericTypeSpecialization(
 const container::DataType type, const Functor functor = Functor()) {
  switch (type) {
  case container::INT32:     return functor.operator()<container::INT32>();
  case container::INT64:     return functor.operator()<container::INT64>();
  case container::UINT32:    return functor.operator()<container::UINT32>();
  case container::UINT64:    return functor.operator()<container::UINT64>();
  case container::FLOAT:     return functor.operator()<container::FLOAT>();
  case container::DOUBLE:    return functor.operator()<container::DOUBLE>();
  case container::BOOL:
  case container::DATE:
  case container::DATETIME:
  case container::STRING:
  case container::BINARY:
  case container::ENUM:
  case container::DATA_TYPE:
   THROW(new container::Exception(
    container::ERROR_INVALID_ARGUMENT_TYPE,
    StrCat("Non-numeric DataType ", container::DataType_Name(type), " passed to "
                 "NumericTypeSpecialization.")));
  }
  LOG(FATAL) << "Unknown DataType: " << type;
}

#define CPP_TYPE(type) typename container::TypeTraits<type>::cpp_type

// A template function that appends a string representation of a typed value
// to the specified string. (Specializations defined in the .cc file).
template<container::DataType type>
void PrintTyped(const CPP_TYPE(type)& value, std::string* target);

// A template for creating the string representation of a typed value in a
// StringPiece.
// The specialization for the STRING type does not copy the data, so the result
// is valid as long as the original StringPiece is valid.
// The specializations for other types contain an internal string field, so the
// content is guaranteed to be valid as long as this object is kept around and
// not reused.
template<container::DataType type>
struct AsString {
  base::StringPiece operator()(const CPP_TYPE(type)& value) {
    value_storage_ = "";
    PrintTyped<type>(value, &value_storage_);
    return value_storage_;
  }

 private:
  std::string value_storage_;
};

template<>
struct AsString<container::STRING> {
  base::StringPiece operator()(const base::StringPiece& value) { return value; }
};

// A template function that parses a typed value from string. (Specializations
// are defined in the .cc file).
template<container::DataType type>
bool ParseTyped(const char* value, CPP_TYPE(type)* target);

enum ComparisonResult {
  RESULT_LESS             = -1,
  RESULT_EQUAL            =  0,
  RESULT_EQUAL_NULL       =  1,
  RESULT_GREATER          =  2,
  RESULT_GREATER_OR_EQUAL =  3,  // Returned by 'weak' comparators.
};

template<container::DataType left_type, container::DataType right_type, bool weak>
inline ComparisonResult ThreeWayCompare(const CPP_TYPE(left_type)& left,
                                        const CPP_TYPE(right_type)& right) {
  container::operators::Less less;
  if (less(left, right)) return RESULT_LESS;
  if (weak) return RESULT_GREATER_OR_EQUAL;
  if (less(right, left)) return RESULT_GREATER;
  return RESULT_EQUAL;
}

// Specializations for variable-length types.
template<bool weak>
inline ComparisonResult ThreeWayStringCompare(const base::StringPiece& left,
                                              const base::StringPiece& right) {
  const int r = memcmp(left.data(), right.data(),
                       min(left.size(), right.size()));
  if (r < 0) return RESULT_LESS;
  if (r > 0) return weak ? RESULT_GREATER_OR_EQUAL : RESULT_GREATER;
  if (left.size() < right.size()) return RESULT_LESS;
  if (weak) return RESULT_GREATER_OR_EQUAL;
  if (left.size() > right.size()) return RESULT_GREATER;
  return RESULT_EQUAL;
}

template<>
inline ComparisonResult ThreeWayCompare<container::STRING, container::STRING, false>(
    const base::StringPiece& left, const base::StringPiece& right) {
  return ThreeWayStringCompare<false>(left, right);
}

template<>
inline ComparisonResult ThreeWayCompare<container::STRING, container::STRING, true>(
    const base::StringPiece& left, const base::StringPiece& right) {
  return ThreeWayStringCompare<true>(left, right);
}

template<>
inline ComparisonResult ThreeWayCompare<container::BINARY, container::BINARY, false>(
    const base::StringPiece& left, const base::StringPiece& right) {
  return ThreeWayStringCompare<false>(left, right);
}

template<>
inline ComparisonResult ThreeWayCompare<container::BINARY, container::BINARY, true>(
    const base::StringPiece& left, const base::StringPiece& right) {
  return ThreeWayStringCompare<true>(left, right);
}

template<container::DataType left_type, container::DataType right_type,
         bool left_not_null, bool right_not_null,
         bool weak, bool ignore_equal_null>
inline ComparisonResult ThreeWayCompareWithNulls(
    const CPP_TYPE(left_type)* const left,
    const CPP_TYPE(right_type)* const right) {
  DCHECK(!(right == NULL && right_not_null));
  DCHECK(!(left == NULL && left_not_null));
  if (!right_not_null && right == NULL) {
    if (weak) return RESULT_GREATER_OR_EQUAL;
    if (!left_not_null && left == NULL) {
      return ignore_equal_null ? RESULT_EQUAL : RESULT_EQUAL_NULL;
    } else {
      return RESULT_GREATER;
    }
  }
  if (!left_not_null && left == NULL) return RESULT_LESS;
  return ThreeWayCompare<left_type, right_type, weak>(*left, *right);
}

// Templatized comparators and other functions.

// Equality comparator.
template<container::DataType left_type, container::DataType right_type,
         bool left_not_null, bool right_not_null>
struct EqualityWithNullsComparator {
  bool operator()(const CPP_TYPE(left_type)* const left,
                  const CPP_TYPE(right_type)* const right) const {
   container::operators::Equal equal;
    if (!left_not_null && left == NULL) {
      return (!right_not_null && right == NULL);
    } else {
      return (right_not_null || right != NULL) && equal(*left, *right);
    }
  }
};

// Inequality comparator (Swiss-army-knife).
// If descending, the sort order is inverted.
// If weak, does not distinguish between RESULT_EQUAL, RESULT_EQUAL_NULL, and
// RESULT_GREATER (only returns RESULT_LESS and RESULT_GREATER_OR_EQUAL)
// If ignore_equal_null, does not distinguish between RESULT_EQUAL and
//   RESULT_EQUAL_NULL (returns RESULT_EQUAL if non-weak and both operands are
//   NULL).
template<container::DataType left_type, container::DataType right_type,
         bool left_not_null, bool right_not_null,
         bool descending, bool weak, bool ignore_equal_null>
struct InequalityWithNullsComparator {
  ComparisonResult operator()(const CPP_TYPE(left_type)* const left,
                              const CPP_TYPE(right_type)* const right) const {
    if (!descending) {
      return ThreeWayCompareWithNulls<
          left_type, right_type, left_not_null, right_not_null,
          weak, ignore_equal_null>(left, right);
    } else {
      return ThreeWayCompareWithNulls<
          right_type, left_type, right_not_null, left_not_null,
          weak, ignore_equal_null>(right, left);
    }
  }
};

template<container::DataType type>
struct ShallowDatumCopy {
  void operator()(const CPP_TYPE(type)& input, CPP_TYPE(type)* output) {
    DCHECK(output != NULL) << "The output must not be NULL";
    *output = input;
  }
};

template<container::DataType type,
         bool deep_copy = container::TypeTraits<type>::is_variable_length,
         bool is_variable_length = container::TypeTraits<type>::is_variable_length>
struct DatumCopy {
  bool operator()(const CPP_TYPE(type)& input,
                  CPP_TYPE(type)* const output,
                  container::Arena* const arena) {
    ShallowDatumCopy<type> copy;
    copy(input, output);
    return true;
  }
};

// Partial specialization for variable-length types, copying of which involves
// writing a copy of the variable-length data buffer into output column's arena.
// Only used if type is both variable-length and deep copying is requested.
template <container::DataType type>
struct DatumCopy<type, true, true> {
  // Can return false only if data being copied is of
  // variable-length type, deep copying is requested, and the destination arena
  // can't accommodate a copy of a variable-length data buffer.
  bool operator()(const base::StringPiece& input,
                  base::StringPiece* const output,
                  container::Arena* const arena) {
    // For variable-length types cpp_type is StringPiece.
    const char* copy = arena->AddStringPieceContent(input);
    if (copy == NULL) {
      LOG(WARNING) << "Deep copy failed, size of input is " << input.size();
      return false;
    } else {
      output->set(copy, input.size());
      return true;
    }
  }
};

// Computes a hash value for a single datum, possibly NULL.
// Hash function has to satisfy following conditions:
// -it is at least 64-bit long (like size_t)
// -no different data not null of type T can produce same hash, where T is in
// {INT32, UINT32, INT64, UINT64, BOOL}
template<container::DataType type, typename Hasher, bool is_not_null>
struct HashComputer {
  size_t operator()(const CPP_TYPE(type)* const datum) const {
    if (!is_not_null && datum == NULL) {
      return 0xdeadbabe;
    } else {
      Hasher hasher;
      return hasher(*datum);
    }
  }
};

// Computes hash values for a column of data, possibly with NULL values.
// The result of hashing is written to the 'hashes' array. If 'update',
// the existing hashes are adjusted so that the result is a 'cumulative hash'.
// Otherwise, 'hashes' are overwritten.
template<container::DataType type, typename Hasher, bool update, bool is_not_null>
struct ColumnHashComputer {
  void operator()(const CPP_TYPE(type)* const data,
   container::bool_const_ptr is_null,
                  size_t const row_count,
                  size_t* hashes) const {
    Hasher hasher;
    for (container::rowcount_t i = 0; i < row_count; ++i) {
      size_t item_hash;
      // We're relying on the compiler to take advantage of the constness of
      // is_null, and pre-compute (is_null != NULL).
      if (!is_not_null && is_null != NULL && *is_null) {
        item_hash = 0xdeadbabe;
      } else {
        item_hash = hasher(data[i]);
      }
      // We rely on the compiler to precompute the condition, so there will
      // be no branching here.
      if (!is_not_null && is_null != NULL) ++is_null;
      hashes[i] = update ? hashes[i] * 29 + item_hash : item_hash;
    }
  }
};

// Prototypes of functions that can perform type-specific operations. Arguments
// to these functions are declared as VariantPointer's, since their type
// is not known at compile time. Each such function, however, 'knows' the type
// of arguments it is expected to handle, and can cast it to to the right thing.
// Some functions operate on single items, some on pairs of items (of possibly
// different types), and some on columns.

// Prototype of a function that appends a formatted typed value to a string.
typedef void(*AttributePrinter)(container::VariantConstPointer value, string* target);

// Prototype of a function that parses a typed POD value from a string.
typedef bool(*AttributeParser)(const char* value, container::VariantPointer target);

// Prototype of a function that compares two typed values for in/equality,
// and gives a boolean result.
typedef bool(*EqualityComparator)(container::VariantConstPointer left,
 container::VariantConstPointer right);

// Prototype of a function that compares two typed values for inequality.
typedef ComparisonResult(*InequalityComparator)(container::VariantConstPointer left,
 container::VariantConstPointer right);

// Prototype of a function that computes a hash code for a single item.
typedef size_t(*Hasher)(container::VariantConstPointer datum);

// Prototype of a function that computes or updates hash codes for a column
// of data.
typedef void(*ColumnHasher)(container::VariantConstPointer data,
 container::bool_const_ptr is_null,
                             size_t row_count,
                             size_t* hashes);

// Returns a function that knows how to write the attribute to string.
// NULLs are written as "NULL". Appends the result at the end of the supplied
// string.
AttributePrinter GetDefaultPrinterFn(container::DataType type);

// Returns a function that knows how to parse an attribute from a string.
// Returns true if successfully parsed a non-NULL value and modified the
// target; false otherwise. NULL pointers and unparsable numbers translate
// to NULL.
// NOTE: this function is not defined for variable-length types, and for
// the ENUM type.
AttributeParser GetDefaultParserFn(container::DataType type);

// Returns a function that can be used in a sort comparator. Normally,
// it returns one of RESULT_LESS, RESULT_EQUAL, RESULT_GREATER. (unless
//   'terminal' is true; see below).
// * If descending, the order is reverted.
// * If is_not_null, the function skips NULL-checks.
// * If terminal, the check for RESULT_GREATER is skipped - the function
//   returns RESULT_LESS if a < b (modulo descending) and
//   RESULT_GREATER_OR_EQUAL otherwise. You can use it to faster compare the
//   last attribute in the sort key.
InequalityComparator GetSortComparator(container::DataType type,
                                       bool descending,
                                       bool is_not_null,
                                       bool terminal);

// Returns a function that computes a hash value for a single datum.
// If 'is_not_null', the returned function will assume that the
// datum != NULL, and skip the check.
Hasher GetHasher(container::DataType type, bool is_not_null);

// Returns a function that can computes (or updates) hash values for a
// column of data, given a column. If 'update' is true, the returned function
// will cause existing hash data to be updated; otherwise it will be
// overwritten. If 'is_not_null', the returned function will assume that all
// the data in the vector is not NULL, and omit some NULL-checks.
ColumnHasher GetColumnHasher(container::DataType type, bool update, bool is_not_null);

// Returns a function for computing (left == right).
EqualityComparator GetEqualsComparator(container::DataType left_type,
 container::DataType right_type,
 bool left_not_null,
 bool right_not_null);

// Returns a function for computing relative order of two attributes,
// for MergeJoin. When called, the function returns RESULT_LESS,
// RESULT_GREATER, RESULT_EQUAL, or RESULT_EQUAL_NULL. If 'descending' is true,
// the order is reversed.
InequalityComparator GetMergeComparator(container::DataType left_type,
 container::DataType right_type,
 bool left_not_null,
 bool right_not_null,
 bool descending);

#undef CPP_TYPE

#endif  // IMAGE_BASE_INFRASTRUCTURE_TYPES_INFRASTRUCTURE_H_
