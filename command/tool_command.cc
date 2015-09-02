// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "command/tool_command.h"

namespace command {

ToolCommand::ToolCommand(std::string text) : text_(std::move(text)) {

}

ToolCommand::~ToolCommand() {

}

const std::string& ToolCommand::Text() const {
 return text_;
}

}