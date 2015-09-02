// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMAND_COMMAND_TOOL_H__
#define COMMAND_COMMAND_TOOL_H__

#include <string>

#include "base/command_line.h"

namespace command {
class Screen;

class CommandTool {
public:
 virtual ~CommandTool(){}

 virtual const std::string& tool_name() const = 0;

 virtual bool Parse(const base::CommandLine& cmd) = 0;
 virtual void Run() = 0;
 virtual void PrintHelp(Screen* screen) = 0;

};

}

#endif