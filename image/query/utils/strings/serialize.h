// Copyright 2010 Google Inc. All Rights Reserved.
// Refactored from contributions of various authors in strings/strutil.h
//
// This file contains conversion functions from various data types to
// strings and back.

#ifndef STRINGS_SERIALIZE_H_
#define STRINGS_SERIALIZE_H_

#include <string.h>
#include <unordered_map>
#include <string>
namespace image {using std::string; }
#include <utility>
#include <vector>
using std::vector;

#include <type_traits>
#include "base/logging.h"
#include "base/strings/string_piece.h"
#include "image/query/utils/int128.h"
#include "image/query/utils/endian.h"
#include "image/query/utils/stl_util.h"

// Converts a 4-byte uint32 to a string such that the string keys sort in
// the same order as the original uint32 value.
// TODO(user): Rework all reinterpret_casts<> in this file.
inline void KeyFromUint32(uint32 u32, std::string* key) {
  uint32 norder = ghtonl(u32);
  key->assign(reinterpret_cast<const char*>(&norder), sizeof(norder));
}

// Converts "fp" to an 8-byte string key
inline void KeyFromUint64(uint64 fp, std::string* key) {
  uint64 norder = htonll(fp);
  key->assign(reinterpret_cast<const char*>(&norder), sizeof(norder));
}

// Converts a 16-byte uint128 to a string such that the string keys sort in
// the same order as the original uint128 value.
inline void KeyFromUint128(uint128 fp, std::string* key) {
  uint64 norder[] = { htonll(Uint128High64(fp)),
                      htonll(Uint128Low64(fp))
  };
  key->assign(reinterpret_cast<const char*>(norder), 2 * sizeof(norder[0]));
}

// This version of KeyFromUint32 is less efficient but very convenient
std::string Uint32ToKey(uint32 u32);

// This version of KeyFromUint64 is less efficient but very convenient
std::string Uint64ToKey(uint64 fp);

// This version of KeyFromUint128 is less efficient but very convenient
std::string Uint128ToKey(uint128 u128);

// Converts a 4-byte string key (typically generated by KeyFromUint32 or
// Uint32ToKey) into a uint32 value.
inline uint32 KeyToUint32(base::StringPiece key) {
  uint32 value;
  DCHECK_EQ(key.size(), sizeof(value));
  memcpy(&value, key.data(), sizeof(value));
  return gntohl(value);
}

// Converts an 8-byte string key (typically generated by Uint64ToKey or
// KeyFromUint64) into a uint64 value
inline uint64 KeyToUint64(base::StringPiece key) {
  uint64 value;
  DCHECK_EQ(key.size(), sizeof(value));
  memcpy(&value, key.data(), sizeof(value));
  return ntohll(value);
}

// Converts a 16-byte string key (typically generated by Uint128ToKey or
// KeyFromUint128) into a uint128 value
inline uint128 KeyToUint128(base::StringPiece key) {
  uint64 v0, v1;
  DCHECK_EQ(key.size(), sizeof(v0) + sizeof(v1));
  memcpy(&v0, key.data(), sizeof(v0));
  memcpy(&v1, key.data() + sizeof(v0), sizeof(v1));
  return uint128(ntohll(v0), ntohll(v1));
}

// Converts "i32" to a 4-byte string key
// NOTE: Lexicographic ordering of the resulting strings does not in
// general correspond to any natural ordering of the corresponding
// integers. For non-negative inputs, lexicographic ordering of the
// resulting strings corresponds to increasing ordering of the
// integers. However, negative inputs are sorted *after* the non-negative
// inputs. To obtain keys such that lexicographic ordering corresponds
// to the natural total order on the integers, use OrderedStringFromInt32()
// or ReverseOrderedStringFromInt32() instead.
void KeyFromInt32(int32 i32, std::string* key);

// Convenient form of KeyFromInt32.
inline std::string Int32ToKey(int32 i32) {
  std::string s;
  KeyFromInt32(i32, &s);
  return s;
}

// Converts a 4-byte string key (typically generated by KeyFromInt32)
// into an int32 value
int32 KeyToInt32(base::StringPiece key);

// Converts a double value to an 8-byte string key, so that
// the string keys sort in the same order as the original double values.
void KeyFromDouble(double x, std::string* key);

// Converts key generated by KeyFromDouble() back to double.
double KeyToDouble(base::StringPiece key);

// This version of KeyFromDouble is less efficient but very convenient
std::string DoubleToKey(double x);

// Converts int32 to a 4-byte string key such that lexicographic
// ordering of strings is equivalent to sorting in increasing order by
// integer values. This can be useful when constructing secondary
void OrderedStringFromInt32(int32 i32, std::string* key);

// This version of OrderedStringFromInt32 is less efficient but very convenient
std::string Int32ToOrderedString(int32 i32);

// The inverse of the above function.
int32 OrderedStringToInt32(base::StringPiece key);

// Converts int64 to an 8-byte string key such that lexicographic
// ordering of strings is equivalent to sorting in increasing order by
// integer values.
void OrderedStringFromInt64(int64 i64, std::string* key);

// This version of OrderedStringFromInt64 is less efficient but very convenient
std::string Int64ToOrderedString(int64 i64);

// The inverse of the above function.
int64 OrderedStringToInt64(base::StringPiece key);

// Converts int32 to a 4-byte string key such that lexicographic
// ordering of strings is equivalent to sorting in decreasing order
// by integer values. This can be useful when constructing secondary
void ReverseOrderedStringFromInt32(int32 i32, std::string* key);

// This version of ReverseOrderedStringFromInt32 is less efficient but very
std::string Int32ToReverseOrderedString(int32 i32);

// The inverse of the above function.
int32 ReverseOrderedStringToInt32(base::StringPiece key);

// Converts int64 to an 8-byte string key such that lexicographic
// ordering of strings is equivalent to sorting in decreasing order
// by integer values. This can be useful when constructing secondary
void ReverseOrderedStringFromInt64(int64 i64, std::string* key);

// This version of ReverseOrderedStringFromInt64 is less efficient but very
std::string Int64ToReverseOrderedString(int64 i64);

// The inverse of the above function.
int64 ReverseOrderedStringToInt64(base::StringPiece key);

// Stores the bytes of a plain old data type value in a C++ string.
// Verifies the given data type is a POD and copies the bytes of the
// value into a newly created string.
//
// Can replace the use of Encode*, and avoid the use of castings,
// or adding additional functions for each type.
// For example, use:
//   int32 i = 100;
//   string s = EncodePOD(i);
// in place of:
//   string s = EncodeUint32(static_cast<uint32>(i));
template <typename T> inline string EncodePOD(const T& value) {
//  ENFORCE_POD(T);
  string s;
  STLStringResizeUninitialized(&s, sizeof(T));
  memcpy(string_as_array(&s), &value, sizeof(T));
  return s;
}

// Retrieves the bytes of a plain old data type value from a StringPiece.
// Verifies the given data type is a POD and copies the bytes of the
// value from the given string.
// Returns true if the operation succeeded.
// Note that other than the data length, no check is (or can be)
// done on the type of data stored in the string.
//
// Can replace the use of Decode*, and avoid the use of castings,
// or adding additional functions for each type.
// For example, use:
//   int32 i = 100;
//   int32 j;
//   string s = EncodePOD(i);
//   CHECK(DecodePOD(s, &j));
// in place of:
//   string s = EncodeUint32(static_cast<uint32>(i));
//   CHECK(DecodesUint32(s, static_cast<uint32*>(&j)));
template <typename T> inline bool DecodePOD(base::StringPiece str, T* result) {
//  ENFORCE_POD(T);
  CHECK(result != NULL);
  if (sizeof(*result) != str.size()) {
    return false;
  }
  memcpy(result, str.data(), sizeof(T));
  return true;
}

// Stores the value bytes of a vector of plain old data type in a C++ string.
// Verifies the given data type is a POD and copies the bytes of each value
// in the vector into a newly created string.
template <typename T> inline string EncodeVectorPOD(const vector<T>& vec) {
  ENFORCE_POD(T);
  string s;
  STLStringResizeUninitialized(&s, vec.size() * sizeof(T));
  typename vector<T>::const_iterator iter;
  char* ptr;
  for (iter = vec.begin(), ptr = string_as_array(&s);
       iter != vec.end();
       ++iter, ptr += sizeof(T)) {
    memcpy(ptr, &(*iter), sizeof(T));
  }
  return s;
}

// Reconstructs a vector of a plain old data type values from a C++ string.
// Verifies the given data type is a POD and copies the bytes of each value
// from the given string to the given vector.
// Returns true if the operation succeeded.
// Note that other than the data length, no check is (or can be)
// done on the type of data stored in the string.
template <typename T> inline bool DecodeVectorPOD(const string& str,
                                                  vector<T>* result) {
  ENFORCE_POD(T);
  CHECK(result != NULL);
  if (str.size() % sizeof(T) != 0)
    return false;
  result->clear();
  result->reserve(str.size() / sizeof(T));
  T value;
  const char* begin = str.data();
  const char* end = str.data() + str.size();
  for (const char* ptr = begin; ptr != end; ptr += sizeof(T)) {
    memcpy(&value, ptr, sizeof(T));
    result->push_back(value);
  }
  return true;
}

// ----------------------------------------------------------------------
// EncodeDouble()
// EncodeFloat()
// EncodeUint32()
// EncodeUint64()
// DecodeDouble()
// DecodeFloat()
// DecodeUint32()
// DecodeUint64()
//    The Encode* functions store the bytes of ints, floats or doubles into the
//    data bytes of a C++ string.  The Decode* functions perform the reverse
//    operations, but operate on a StringPiece rather than directly on a C++
//    string.  They return true iff s contained the right number of bytes.
//
//    These may be preferred to naked calls to EncodePOD/DecodePOD since
//    they make the payload type explicit.
//    Note that these encodings are NOT endian-neutral.
// ----------------------------------------------------------------------
inline std::string EncodeDouble(double d) {
  return EncodePOD(d);
}

inline std::string EncodeFloat(float f) {
  return EncodePOD(f);
}

inline std::string EncodeUint32(uint32 i) {
  return EncodePOD(i);
}

inline std::string EncodeUint64(uint64 i) {
  return EncodePOD(i);
}

inline bool DecodeDouble(base::StringPiece s, double* d) {
  return DecodePOD(s, d);
}

inline bool DecodeFloat(base::StringPiece s, float* f) {
  return DecodePOD(s, f);
}

inline bool DecodeUint32(base::StringPiece s, uint32* i) {
  return DecodePOD(s, i);
}

inline bool DecodeUint64(base::StringPiece s, uint64* i) {
  return DecodePOD(s, i);
}

// -------------------------------------------------------------------------
// DictionaryParse
//   This routine parses a common dictionary format (key and value separated
//   by ':', entries separated by commas). This format is used for many
//   complex commandline flags. It is also used to encode dictionaries for
//   exporting them or writing them to a checkpoint. Returns a vector of
//   <key, value> pairs. Returns true if there if no error in parsing, false
//    otherwise.
// -------------------------------------------------------------------------
bool DictionaryParse(const std::string& encoded_str,
 vector<std::pair<std::string, std::string> >* items);

// --------------------------------------------------------------------------
// DictionaryInt32Encode
// DictionaryInt64Encode
// DictionaryDoubleEncode
// DictionaryInt32Decode
// DictionaryInt64Decode
// DictionaryDoubleDecode
//   Routines to serialize/unserialize simple dictionaries
//   (string->T hashmaps). These are useful for exporting, checkpointing etc
//   *Decode routines clear the input dictionary. They return true if there
//   was no error in decoding, false otherwise.
//   Note: these routines are not meant for use with very large dictionaries.
//   They are written for convenience and not efficiency.
// --------------------------------------------------------------------------
std::string DictionaryInt32Encode(const std::unordered_map<std::string, int32>* dictionary);
std::string DictionaryInt64Encode(const std::unordered_map<std::string, int64>* dictionary);
std::string DictionaryDoubleEncode(const std::unordered_map<std::string, double>* dictionary);

bool DictionaryInt32Decode(std::unordered_map<std::string, int32>* dictionary,
 const std::string& encoded_str);
bool DictionaryInt64Decode(std::unordered_map<std::string, int64>* dictionary,
 const std::string& encoded_str);
bool DictionaryDoubleDecode(std::unordered_map<std::string, double>* dictionary,
 const std::string& encoded_str);


#endif  // STRINGS_SERIALIZE_H_
