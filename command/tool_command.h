// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMAND_TOOL_COMMAND_H__
#define COMMAND_TOOL_COMMAND_H__

#include <string>

#include "base/basictypes.h"

namespace command {

class ToolCommand {
public:
 ToolCommand(std::string text);
 ~ToolCommand();

 size_t lenght() const { return text_.length(); }

 const std::string& Text() const;

private:

 std::string text_;

 DISALLOW_COPY_AND_ASSIGN(ToolCommand);
};
}

#endif