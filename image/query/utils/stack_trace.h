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
//          jelonka@google.com (Ilona Gaweda)
//
// Encapsulation of errors.

#ifndef DATAWAREHOUSE_COMMON_EXCEPTION_STACK_TRACE_H_
#define DATAWAREHOUSE_COMMON_EXCEPTION_STACK_TRACE_H_

#include <string>
#include <vector>

#include "base/strings/string_piece.h"
#include "image/query/utils/stack_trace.pb.h"

namespace image {

void AddStackTraceElement(const base::StringPiece& function,
 const base::StringPiece& filename,
 int line,
 const base::StringPiece& context,
 StackTrace* trace);

// Appends a dump of the stack trace to the specified out string. For
// convenience, returns a const reference to *out.
const std::string& AppendStackTraceDump(const StackTrace& trace, std::string* out);

}  // namespace

#endif  // DATAWAREHOUSE_COMMON_EXCEPTION_STACK_TRACE_H_
