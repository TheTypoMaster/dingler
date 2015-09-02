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

#include "image/query/utils/stack_trace.h"

#include "base/memory/scoped_ptr.h"
#include "base/strings/stringprintf.h"


namespace image {

const std::string& AppendStackTraceDump(const StackTrace& trace, std::string* out) {
  for (int i = 0; i < trace.element_size(); ++i) {
    const StackTrace::Element& element = trace.element(i);
    base::StringAppendF(out,
                  "    at %s(%s:%d) %s\n",
                  element.function().c_str(), element.filename().c_str(),
                  element.line(), element.context().c_str());
  }
  return *out;
}

void AddStackTraceElement(const base::StringPiece& function,
 const base::StringPiece& filename,
 int line,
 const base::StringPiece& context,
 StackTrace* trace) {
  StackTrace::Element* new_element = trace->add_element();
  new_element->set_function(function.as_string());
  new_element->set_filename(filename.as_string());
  new_element->set_line(line);
  new_element->set_context(context.as_string());
}

}  // namespace

