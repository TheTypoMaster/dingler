// Copyright 2010 Google Inc. All Rights Reserved.
// Refactored from contributions of various authors in strings/strutil.cc
//
// This file contains string processing functions related to
// uppercase, lowercase, etc.

#include "image/query/utils/strings/case.h"

#include <string>

#include "base/strings/string_piece.h"
#include "image/query/utils/strings/ascii_ctype.h"
#include "image/query/utils/strings/memutil.h"

CapsType GetCapitalization(const char* s) {
  // find the caps type of the first alpha char
  for (; *s && !(ascii_isupper(*s) || ascii_islower(*s)); ++s) {}
  if (!*s) return CAPS_NOALPHA;
  const CapsType firstcapstype = (ascii_islower(*s)) ? CAPS_LOWER : CAPS_UPPER;

  // skip ahead to the next alpha char
  for (++s; *s && !(ascii_isupper(*s) || ascii_islower(*s)); ++s) {}
  if (!*s) return firstcapstype;
  const CapsType capstype = (ascii_islower(*s)) ? CAPS_LOWER : CAPS_UPPER;

  if (firstcapstype == CAPS_LOWER &&
      capstype == CAPS_UPPER)
    return CAPS_MIXED;

  for (; *s; ++s)
    if ((ascii_isupper(*s) && capstype != CAPS_UPPER) ||
        (ascii_islower(*s) && capstype != CAPS_LOWER))
      return CAPS_MIXED;

  if (firstcapstype == CAPS_UPPER && capstype == CAPS_LOWER)
    return CAPS_FIRST;
  return capstype;
}

int CaseCompare(base::StringPiece s1, base::StringPiece s2) {
  if (s1.size() == s2.size()) {
    return memcasecmp(s1.data(), s2.data(), s1.size());
  } else if (s1.size() < s2.size()) {
    int res = memcasecmp(s1.data(), s2.data(), s1.size());
    return (res == 0) ? -1 : res;
  } else {
    int res = memcasecmp(s1.data(), s2.data(), s2.size());
    return (res == 0) ? 1 : res;
  }
}

void LowerString(char* s) {
  for (; *s; ++s) {
    *s = ascii_tolower(*s);
  }
}

void LowerString(std::string* s) {
  std::string::iterator end = s->end();
  for (std::string::iterator i = s->begin(); i != end; ++i) {
    *i = ascii_tolower(*i);
  }
}

void LowerStringToBuf(const char* s, char* buf, int n) {
  for (int i = 0; i < n-1; i++) {
    char c = s[i];
    buf[i] = ascii_tolower(c);
    if (c == '\0') {
      return;
    }
  }
  if (n > 0)
    buf[n-1] = '\0';
}

void UpperString(char* s) {
  for (; *s; ++s) {
    *s = ascii_toupper(*s);
  }
}

void UpperString(std::string* s) {
  for (std::string::iterator iter = s->begin(); iter != s->end(); ++iter) {
    *iter = ascii_toupper(*iter);
  }
}

void UpperStringToBuf(const char* s, char* buf, int n) {
  for (int i = 0; i < n-1; i++) {
    char c = s[i];
    buf[i] = ascii_toupper(c);
    if (c == '\0') {
      return;
    }
  }
  if (n > 0)
    buf[n-1] = '\0';
}

void TitlecaseString(std::string *s, base::StringPiece delimiters) {
  bool upper = true;
  for (std::string::iterator ss = s->begin(); ss != s->end(); ++ss) {
    if (upper) {
      *ss = ascii_toupper(*ss);
    }
    upper = (delimiters.find(*ss) != base::StringPiece::npos);
  }
}
