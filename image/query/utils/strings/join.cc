// Copyright 2008 and onwards Google Inc.  All rights reserved.

#include "image/query/utils/strings/join.h"

#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "image/query/utils/strings/ascii_ctype.h"
#include "image/query/utils/strings/escaping.h"

// ----------------------------------------------------------------------
// JoinCSVLine()
//    This function is the inverse of SplitCSVLineWithDelimiter() in that the
//    string returned by JoinCSVLineWithDelimiter() can be passed to
//    SplitCSVLineWithDelimiter() to get the original string vector back.
//    Quotes and escapes the elements of original_cols according to CSV quoting
//    rules, and the joins the escaped quoted strings with commas using
//    JoinStrings().  Note that JoinCSVLineWithDelimiter() will not necessarily
//    return the same string originally passed in to
//    SplitCSVLineWithDelimiter(), since SplitCSVLineWithDelimiter() can handle
//    gratuitous spacing and quoting. 'output' must point to an empty string.
//
//    Example:
//     [Google], [x], [Buchheit, Paul], [string with " quoite in it], [ space ]
//     --->  [Google,x,"Buchheit, Paul","string with "" quote in it"," space "]
// ----------------------------------------------------------------------
void JoinCSVLineWithDelimiter(const vector<std::string>& cols, char delimiter,
                              std::string* output) {
  CHECK(output);
  CHECK(output->empty());
  vector<std::string> quoted_cols;

  const std::string delimiter_str(1, delimiter);
  const std::string escape_chars = delimiter_str + "\"";

  // If the string contains the delimiter or " anywhere, or begins or ends with
  // whitespace (ie ascii_isspace() returns true), escape all double-quotes and
  // bracket the string in double quotes. string.rbegin() evaluates to the last
  // character of the string.
  for (int i = 0; i < cols.size(); ++i) {
    if ((cols[i].find_first_of(escape_chars) != std::string::npos) ||
        (!cols[i].empty() && (ascii_isspace(*cols[i].begin()) ||
                              ascii_isspace(*cols[i].rbegin())))) {
      // Double the original size, for escaping, plus two bytes for
      // the bracketing double-quotes, and one byte for the closing \0.
      int size = 2 * cols[i].size() + 3;
      scoped_ptr<char[]> buf(new char[size]);

      // Leave space at beginning and end for bracketing double-quotes.
      int escaped_size = strings::EscapeStrForCSV(cols[i].c_str(),
                                                  buf.get() + 1, size - 2);
      CHECK_GE(escaped_size, 0) << "Buffer somehow wasn't large enough.";
      CHECK_GE(size, escaped_size + 3)
        << "Buffer should have one space at the beginning for a "
        << "double-quote, one at the end for a double-quote, and "
        << "one at the end for a closing '\0'";
      *buf.get() = '"';
      *((buf.get() + 1) + escaped_size) = '"';
      *((buf.get() + 1) + escaped_size + 1) = '\0';
      quoted_cols.push_back(std::string(buf.get(), buf.get() + escaped_size + 2));
    } else {
      quoted_cols.push_back(cols[i]);
    }
  }
  JoinStrings(quoted_cols, delimiter_str, output);
}

void JoinCSVLine(const vector<std::string>& cols, std::string* output) {
  JoinCSVLineWithDelimiter(cols, ',', output);
}

std::string JoinCSVLine(const vector<std::string>& cols) {
  std::string output;
  JoinCSVLine(cols, &output);
  return output;
}
