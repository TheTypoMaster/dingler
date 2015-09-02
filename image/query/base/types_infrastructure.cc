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

#include "image/query/base/types_infrastructure.h"

#include <time.h>

#include <cmath>
#include <limits>
#include <string>

#include "base/basictypes.h"
#include "base/strings/stringprintf.h"
#include "image/query/utils/strings/numbers.h"
#include "image/query/utils/strings/strip.h"
#include "image/query/utils/walltime.h"

namespace {

const char* const kDefaultDateTimeParseFormat = " %Y/%m/%d-%H:%M:%S ";
const char* const kDefaultDateTimePrintFormat = "%Y/%m/%d-%H:%M:%S";

const char* const kDefaultDateParseFormat = " %Y/%m/%d ";
const char* const kDefaultDatePrintFormat = "%Y/%m/%d";

}  // end anonymous namespace

// Specializations of PrintTyped.

template<> void PrintTyped<container::INT32>(const int32& value, std::string* const target) {
  char buffer[kFastToBufferSize];
  target->append(FastInt32ToBuffer(value, buffer));
}

template<> void PrintTyped<container::UINT32>(const uint32& value, std::string* const target) {
  char buffer[kFastToBufferSize];
  target->append(FastUInt32ToBuffer(value, buffer));
}

template<> void PrintTyped<container::INT64>(const int64& value, std::string* const target) {
  char buffer[kFastToBufferSize];
  target->append(FastInt64ToBuffer(value, buffer));
}

template<> void PrintTyped<container::UINT64>(const uint64& value, std::string* const target) {
  char buffer[kFastToBufferSize];
  target->append(FastUInt64ToBuffer(value, buffer));
}

template<> void PrintTyped<container::FLOAT>(const float& value, std::string* const target) {
  target->append(SimpleFtoa(value));
}

template<> void PrintTyped<container::DOUBLE>(const double& value, std::string* const target) {
  target->append(SimpleDtoa(value));
}

template<> void PrintTyped<container::BOOL>(const bool& value, std::string* const target) {
  target->append((value) ? "TRUE" : "FALSE");
}

template<> void PrintTyped<container::ENUM>(const int32& value, std::string* const target) {
  // NOTE: usually, this default won't be used; the higher-level function
  // (e.g. ViewPrinter) will handle ENUMs in a special way.
 return PrintTyped<container::INT32>(value, target);
}

template<> void PrintTyped<container::STRING>(const base::StringPiece& value,
                                   string* const target) {
  value.AppendToString(target);
}

// TODO(user): Support for the entire int64 datetime range, print
// microseconds as well.
template<> void PrintTyped<container::DATETIME>(const int64& value, std::string* const target) {
  const time_t time = value / 1000000;
  const size_t previous_size = target->size();
  // Show in UTC.
  StringAppendStrftime(target, kDefaultDateTimePrintFormat, time, false);
  // StringAppendStrftime() reports errors by leaving target unmodified.
  if (target->size() == previous_size) {
    target->append("NULL");
  }
}

// TODO(user): Support for the entire int32 date range.
template<> void PrintTyped<container::DATE>(const int32& value, std::string* const target) {
  const time_t time = value * (24 * 3600);
  const size_t previous_size = target->size();
  // Show in UTC.
  StringAppendStrftime(target, kDefaultDatePrintFormat, time, false);
  // StringAppendStrftime() reports errors by leaving target unmodified.
  if (target->size() == previous_size) {
    target->append("NULL");
  }
}

template<>
void PrintTyped<container::BINARY>(const base::StringPiece& value, std::string* const target) {
 base::StringAppendF(target, "<0x");
  // This is to enforce uniform printing as the signed-ness of the char type is
  // platform dependent.
  const unsigned char* p = reinterpret_cast<const unsigned char*>(value.data());
  for (int i = 0; i < value.size(); ++i) {
    if (i % 4 == 0) base::StringAppendF(target, " ");
    
    base::StringAppendF(target, "%02x", *p++);
  }
  base::StringAppendF(target, ">");
}

template<>
void PrintTyped<container::DATA_TYPE>(const container::DataType& value, std::string* const target) {
 target->append(container::DataType_Name(value));
}

template<container::DataType type>
void DefaultPrinter(const container::VariantConstPointer value, std::string* target) {
  DCHECK(target);
  if (value.is_null()) {
    target->append("NULL");
  } else {
    PrintTyped<type>(*value.as<type>(), target);
  }
}

struct PrinterResolver {
 template<container::DataType type>
  AttributePrinter operator()() const { return &DefaultPrinter<type>; }
};

AttributePrinter GetDefaultPrinterFn(container::DataType type) {
  return TypeSpecialization<AttributePrinter, PrinterResolver>(type);
}

// Specializations of ParseTyped.

template<> bool ParseTyped<container::INT32>(const char* value, int32* target) {
  return safe_strto32(value, target);
}

template<> bool ParseTyped<container::UINT32>(const char* value, uint32* target) {
  return safe_strtou32(value, target);
}

template<> bool ParseTyped<container::INT64>(const char* value, int64* target) {
  return safe_strto64(value, target);
}

template<> bool ParseTyped<container::UINT64>(const char* value, uint64* target) {
  return safe_strtou64(value, target);
}

template<> bool ParseTyped<container::FLOAT>(const char* value, float* target) {
  return safe_strtof(value, target);
}

template<> bool ParseTyped<container::DOUBLE>(const char* value, double* target) {
  return safe_strtod(value, target);
}

template<> bool ParseTyped<container::BOOL>(const char* value, bool* target) {
  // Common case (no trimming needed): avoid malloc.
  if (strcasecmp("true", value) == 0 ||
      strcasecmp("yes", value) == 0) {
    *target = true;
    return true;
  } else if (strcasecmp("false", value) == 0 ||
             strcasecmp("no", value) == 0) {
    *target = false;
    return true;
  } else {
    // Fall back to the version that does the trimming.
    // TODO(user):  Do this without malloc as well.
    string s(value);
    TrimString(&s, " \t\r");
    if (strcasecmp("true", s.c_str()) == 0 ||
        strcasecmp("yes", s.c_str()) == 0) {
      *target = true;
      return true;
    } else if (strcasecmp("false", s.c_str()) == 0  ||
               strcasecmp("no", s.c_str()) == 0) {
      *target = false;
      return true;
    } else {
      return false;
    }
  }
}

// TODO(user):  Fix WallTime_Parse_Timezone():
// - It doesn't handle the time before 1970 correctly (time is set to -1, but
// true is returned).
// - It doesn't accept fractional seconds if the format contains whitespace
// at either ends.
bool ParseDateTime(const std::string& value,
                   const std::string& format,
                   int64* const target) {
  //WallTime time = 0;
  //if (!WallTime_Parse_Timezone(value.c_str(),
  //                             format.c_str(),
  //                             NULL,  // no default value for missing fields
  //                             false,  // use UTC,
  //                             &time)) {
  //  return false;
  //}
  //if (time < 0) {
  //  return false;
  //}
  //const double time_microseconds = floor(time * 1e6 + .5);
  //if (time_microseconds >= numeric_limits<int64>::min() &&
  //    time_microseconds <= numeric_limits<int64>::max()) {
  //  *target = time_microseconds;
  //  return true;
  //} else {
  //  return false;
  //}
  return false;
}

template<>
bool ParseTyped<container::DATETIME>(const char* value, int64* target) {
  return ParseDateTime(value, kDefaultDateTimeParseFormat, target);
}

// TODO(user): Test it after ParseDateTime is fixed (see TODOs above).
template<>
bool ParseTyped<container::DATE>(const char* value, int32* target) {
  int64 time;
  if (ParseDateTime(value, kDefaultDateParseFormat, &time)) {
    // The divisor is > 2^32, so the result won't overflow int32.
    static const int64 microseconds_per_day = 24LL * 3600LL * 1000000LL;
    if (time >= 0) {
      *target = time / microseconds_per_day;
    } else {
      // Revert sign, round up (instead of down), revert sign again.
      *target = -((microseconds_per_day - time - 1) / microseconds_per_day);
    }
    return true;
  } else {
    return false;
  }
}

template<>
bool ParseTyped<container::DATA_TYPE>(const char* value, container::DataType* target) {
 return container::DataType_Parse(string(value), target);
}

template<container::DataType type>
bool DefaultParser(const char* value, const container::VariantPointer target) {
  DCHECK(value != NULL);
  DCHECK(!target.is_null());
  return ParseTyped<type>(value, target.as<type>());
}

template<>
bool DefaultParser<container::ENUM>(const char* value, const container::VariantPointer target) {
  LOG(FATAL) << "Parser for ENUM is not defined";
  return false;
}

template<>
bool DefaultParser<container::STRING>(const char* value, const container::VariantPointer target) {
  LOG(FATAL) << "Parser for STRING is not defined";
  return false;
}

template<>
bool DefaultParser<container::BINARY>(const char* value, const container::VariantPointer target) {
  LOG(FATAL) << "Parser for BINARY is not defined";
  return false;
}

struct ParserResolver {
 template<container::DataType type>
  AttributeParser operator()() const { return &DefaultParser<type>; }
};

AttributeParser GetDefaultParserFn(container::DataType type) {
  return TypeSpecialization<AttributeParser, ParserResolver>(type);
}

// NOTE(user): many of the following aren't used in the existing code, and
// perhaps never will be in the current form. Revisit once we consider the
// API functionally 'code complete'. (i.e. when we have at least MergeUnionAll,
// and MergeJoin).
// TODO(user): reconcile with TypeSpecialization(), at least for stuff like
// GetSortComparator that depends on a single type.

// Following magic is to materialize gozillion function templates and be able
// to return pointers to these functions at run time. The problem, in general,
// is that we have multiple 'dimensions' of specialization: e.g. left type,
// right type, left_not_null, right_not_null, the operator we're interested in
// (hasher, comparator, ...), and often some other properties (descending
// order, ...). General approach is to resolve one dimension at a time, through
// a swith or if statement, and invoke increasingly specialized template
// resolvers.

// Functors to abstract away an operation to be performed on two parameters.
// Each must provide:
// 1. a templatized struct Bind, with
//    1a. operator() that performs the operation in question on two typed
//        parameters;
//    1b. a static method 'Evaluate', accepting two const void* parameters,
//        and calling the operator() with the appropriate static cast;
// 2. typedef RuntimeFunction, declaring the signature of functions that
//    this operation generates.

struct Equal {
 template<container::DataType left_type, container::DataType right_type,
           bool left_not_null, bool right_not_null>
  struct Bind
      : public EqualityWithNullsComparator<left_type, right_type,
                                           left_not_null, right_not_null> {
   static bool Evaluate(const container::VariantConstPointer left,
    const container::VariantConstPointer right) {
      Bind op;
      return op(left.as<left_type>(), right.as<right_type>());
    }
  };
  typedef EqualityComparator RuntimeFunction;
};

// Helper base class for Bind on 'inequality' functors. See
// InequalityWithNullsComparator docstring (types.h) for parameter description.
template<container::DataType left_type, container::DataType right_type,
         bool left_not_null, bool right_not_null,
         bool descending, bool weak, bool ignore_equal_null>
struct Inequality
    : public InequalityWithNullsComparator<left_type, right_type,
                                           left_not_null, right_not_null,
                                           descending, weak,
                                           ignore_equal_null> {
 static ComparisonResult Evaluate(const container::VariantConstPointer left,
  const container::VariantConstPointer right) {
    Inequality op;
    return op(left.as<left_type>(), right.as<right_type>());
  }
};

// Generates functions for non-terminal elements in sort comparators,
// ascending order. These comparators don't distinguish between RESULT_EQUAL
// and RESULT_EQUAL_NULL (returning RESULT_EQUAL in both cases).
struct AscendingSortComparator {
 template<container::DataType left_type, container::DataType right_type,
           bool left_not_null, bool right_not_null>
  struct Bind : public Inequality<left_type, right_type,
                                  left_not_null, right_not_null,
                                  false, false, true> {};
  typedef InequalityComparator RuntimeFunction;
};

// Generates functions for terminal (last) elements in sort comparators,
// ascending order. Such comparators are 'weak' (don't distinguish RESULT_EQUAL
// from RESULT_GREATER), thus a bit cheaper.
struct AscendingSortTerminalComparator {
 template<container::DataType left_type, container::DataType right_type,
           bool left_not_null, bool right_not_null>
  struct Bind : public Inequality<left_type, right_type,
                                  left_not_null, right_not_null,
                                  false, true, true> {};
  typedef InequalityComparator RuntimeFunction;
};

// Generates functions for non-terminal elements in sort comparators,
// descending order. These comparators don't distinguish between RESULT_EQUAL
// and RESULT_EQUAL_NULL (returning RESULT_EQUAL in both cases).
struct DescendingSortComparator {
 template<container::DataType left_type, container::DataType right_type,
           bool left_not_null, bool right_not_null>
  struct Bind : public Inequality<left_type, right_type,
                                  left_not_null, right_not_null,
                                  true, false, true> {};
  typedef InequalityComparator RuntimeFunction;
};

// Generates functions for terminal (last) elements in sort comparators,
// descending order. Such comparators are 'weak' (don't distinguish RESULT_EQUAL
// from RESULT_GREATER), thus a bit cheaper.
struct DescendingSortTerminalComparator {
 template<container::DataType left_type, container::DataType right_type,
           bool left_not_null, bool right_not_null>
  struct Bind : public Inequality<left_type, right_type,
                                  left_not_null, right_not_null,
                                  true, true, true> {};
  typedef InequalityComparator RuntimeFunction;
};

// Generates functions for comparators in merge-joins, ascending order.
// Such comparators always require non-weak semantics, and that RESULT_EQUALS is
// distinguished from RESULT_EQUALS_NULL.
struct AscendingMergeJoinComparator {
 template<container::DataType left_type, container::DataType right_type,
           bool left_not_null, bool right_not_null>
  struct Bind : public Inequality<left_type, right_type,
                                  left_not_null, right_not_null,
                                  false, false, false> {};
  typedef InequalityComparator RuntimeFunction;
};

// Generates functions for comparators in merge-joins, descending order.
// Such comparators always require non-weak semantics, and that RESULT_EQUALS is
// distinguished from RESULT_EQUALS_NULL.
struct DescendingMergeJoinComparator {
 template<container::DataType left_type, container::DataType right_type,
           bool left_not_null, bool right_not_null>
  struct Bind : public Inequality<left_type, right_type,
                                  left_not_null, right_not_null,
                                  true, false, false> {};
  typedef InequalityComparator RuntimeFunction;
};

// The successive resolve magic below.

template<typename Op,
 container::DataType left_type, container::DataType right_type,
         bool left_not_null, bool right_not_null>
typename Op::RuntimeFunction BindComparator() {
  return &Op::template Bind<left_type, right_type,
                            left_not_null, right_not_null>::Evaluate;
}

template<typename Op, container::DataType left_type, container::DataType right_type>
typename Op::RuntimeFunction ResolveComparatorForKnownTypes(
    bool left_not_null,
    bool right_not_null) {
  if (left_not_null) {
    if (right_not_null) {
      return BindComparator<Op, left_type, right_type, true, true>();
    } else {
      return BindComparator<Op, left_type, right_type, true, false>();
    }
  } else {
    if (right_not_null) {
      return BindComparator<Op, left_type, right_type, false, true>();
    } else {
      return BindComparator<Op, left_type, right_type, false, false>();
    }
  }
}

template<typename Op, container::DataType left_type>
typename Op::RuntimeFunction ResolveComparatorForNumericLeftType(
 container::DataType right_type,
    bool left_not_null,
    bool right_not_null) {
  switch (right_type) {
  case container::INT32:
   return ResolveComparatorForKnownTypes<Op, left_type, container::INT32>(
          left_not_null, right_not_null);
  case container::UINT32:
   return ResolveComparatorForKnownTypes<Op, left_type, container::UINT32>(
          left_not_null, right_not_null);
  case container::INT64:
   return ResolveComparatorForKnownTypes<Op, left_type, container::INT64>(
          left_not_null, right_not_null);
  case container::UINT64:
   return ResolveComparatorForKnownTypes<Op, left_type, container::UINT64>(
          left_not_null, right_not_null);
  case container::FLOAT:
   return ResolveComparatorForKnownTypes<Op, left_type, container::FLOAT>(
          left_not_null, right_not_null);
  case container::DOUBLE:
   return ResolveComparatorForKnownTypes<Op, left_type, container::DOUBLE>(
          left_not_null, right_not_null);
    default:
      LOG(FATAL) << "Can't compare numeric type "
       << container::TypeTraits<left_type>::name() << " to non-numeric type "
       << container::GetTypeInfo(right_type).name();
  }
}

template<typename Op>
typename Op::RuntimeFunction ResolveComparatorForHomogeneousTypes(
 container::DataType type,
    bool left_not_null,
    bool right_not_null) {
  switch (type) {
  case container::STRING:
   return ResolveComparatorForKnownTypes<Op, container::STRING, container::STRING>(
          left_not_null, right_not_null);
  case container::BINARY:
     return ResolveComparatorForKnownTypes<Op, container::BINARY, container::BINARY>(
          left_not_null, right_not_null);
  case container::BOOL:
   return ResolveComparatorForKnownTypes<Op, container::BOOL, container::BOOL>(
          left_not_null, right_not_null);
  case container::DATETIME:
   return ResolveComparatorForKnownTypes<Op, container::DATETIME, container::DATETIME>(
          left_not_null, right_not_null);
  case container::DATE:
   return ResolveComparatorForKnownTypes<Op, container::DATE, container::DATE>(
          left_not_null, right_not_null);
  case container::DATA_TYPE:
      // TODO(user): inqeuality (as opposed to equality) should fail.
   return ResolveComparatorForKnownTypes<Op, container::DATA_TYPE, container::DATA_TYPE>(
          left_not_null, right_not_null);
  case container::ENUM:
      // For the purpose of default ordering (e.g. when ORDER BY uses an
      // ENUM column), enums sort and compare by the value number (not name).
   return ResolveComparatorForKnownTypes<Op, container::ENUM, container::ENUM>(
          left_not_null, right_not_null);
    default:
      LOG(FATAL) << "Comparator undefined for type "
       << container::GetTypeInfo(type).name();
  }
}

template<typename Op>
typename Op::RuntimeFunction ResolveComparator(container::DataType left_type,
 container::DataType right_type,
                                               bool left_not_null,
                                               bool right_not_null) {
  switch (left_type) {
  case container::INT32:
   return ResolveComparatorForNumericLeftType<Op, container::INT32>(
          right_type, left_not_null, right_not_null);
  case container::UINT32:
   return ResolveComparatorForNumericLeftType<Op, container::UINT32>(
          right_type, left_not_null, right_not_null);
  case container::INT64:
   return ResolveComparatorForNumericLeftType<Op, container::INT64>(
          right_type, left_not_null, right_not_null);
  case container::UINT64:
   return ResolveComparatorForNumericLeftType<Op, container::UINT64>(
          right_type, left_not_null, right_not_null);
  case container::FLOAT:
   return ResolveComparatorForNumericLeftType<Op, container::FLOAT>(
          right_type, left_not_null, right_not_null);
  case container::DOUBLE:
   return ResolveComparatorForNumericLeftType<Op, container::DOUBLE>(
          right_type, left_not_null, right_not_null);
    default:
      CHECK_EQ(left_type, right_type)
          << "Don't know how to compare non-numeric types "
          << container::GetTypeInfo(left_type).name() << " and "
          << GetTypeInfo(right_type).name();
      return ResolveComparatorForHomogeneousTypes<Op>(
          left_type, left_not_null, right_not_null);
  }
}

struct DefaultSortComparatorResolver {
  DefaultSortComparatorResolver(bool descending,
                                bool is_not_null,
                                bool terminal)
      : descending(descending),
        is_not_null(is_not_null),
        terminal(terminal) {}

  template<container::DataType type>
  InequalityComparator operator()() const {
    if (!terminal) {
      return !descending
        ? ResolveComparatorForKnownTypes<AscendingSortComparator,
                                         type, type>(is_not_null, is_not_null)
        : ResolveComparatorForKnownTypes<DescendingSortComparator,
                                         type, type>(is_not_null, is_not_null);
    } else {
      return !descending
        ? ResolveComparatorForKnownTypes<AscendingSortTerminalComparator,
                                         type, type>(is_not_null, is_not_null)
        : ResolveComparatorForKnownTypes<DescendingSortTerminalComparator,
                                         type, type>(is_not_null, is_not_null);
    }
  }
  bool descending;
  bool is_not_null;
  bool terminal;
};

InequalityComparator GetSortComparator(container::DataType type,
                                       bool descending,
                                       bool is_not_null,
                                       bool terminal) {
  DefaultSortComparatorResolver resolver(descending, is_not_null, terminal);
  return TypeSpecialization<InequalityComparator,
                            DefaultSortComparatorResolver>(type, resolver);
}

template<container::DataType type, bool is_not_null>
size_t DefaultHashComputer(const container::VariantConstPointer datum) {
 HashComputer<type, container::operators::Hash, is_not_null> hash;
  return hash(datum.as<type>());
}

struct DefaultHasherResolver {
  explicit DefaultHasherResolver(bool is_not_null) : is_not_null(is_not_null) {}
  template<container::DataType type>
  Hasher operator()() const {
    if (is_not_null) {
      return &DefaultHashComputer<type, true>;
    } else {
      return &DefaultHashComputer<type, false>;
    }
  }
  bool is_not_null;
};

Hasher GetHasher(container::DataType type, bool is_not_null) {
  DefaultHasherResolver resolver(is_not_null);
  return TypeSpecialization<Hasher,
                            DefaultHasherResolver>(type, resolver);
}

template<container::DataType type, bool update, bool is_not_null>
void DefaultColumnHashComputer(const container::VariantConstPointer data,
 container::bool_const_ptr is_null,
                               size_t const row_count,
                               size_t* hashes) {
 ColumnHashComputer<type, container::operators::Hash, update, is_not_null> hash;
  return hash(data.as<type>(), is_null, row_count, hashes);
}

struct DefaultColumnHasherResolver {
  DefaultColumnHasherResolver(bool update, bool is_not_null)
      : update(update),
        is_not_null(is_not_null) {}
  template<container::DataType type>
  ColumnHasher operator()() const {
    if (update) {
      if (is_not_null) {
        return &DefaultColumnHashComputer<type, true, true>;
      } else {
        return &DefaultColumnHashComputer<type, true, false>;
      }
    } else {
      if (is_not_null) {
        return &DefaultColumnHashComputer<type, false, true>;
      } else {
        return &DefaultColumnHashComputer<type, false, false>;
      }
    }
  }
  bool update;
  bool is_not_null;
};

ColumnHasher GetColumnHasher(container::DataType type, bool update, bool is_not_null) {
  DefaultColumnHasherResolver resolver(update, is_not_null);
  return TypeSpecialization<ColumnHasher,
                            DefaultColumnHasherResolver>(type, resolver);
}

EqualityComparator GetEqualsComparator(container::DataType left_type,
 container::DataType right_type,
                                       bool left_not_null,
                                       bool right_not_null) {
  return ResolveComparator<Equal>(left_type, right_type,
                                  left_not_null, right_not_null);
}

InequalityComparator GetMergeComparator(container::DataType left_type,
 container::DataType right_type,
                                        bool left_not_null,
                                        bool right_not_null,
                                        bool descending) {
  return !descending
    ? ResolveComparator<AscendingMergeJoinComparator>(
        left_type, right_type,
        left_not_null, right_not_null)
    : ResolveComparator<DescendingMergeJoinComparator>(
        left_type, right_type,
        left_not_null, right_not_null);
}

#undef CPP_TYPE
