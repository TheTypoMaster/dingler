// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "command/command_parser.h"

#include "command/command_ast.h"

namespace command {

CommandParser::CommandParser() {
 
}

CommandParser::~CommandParser() {
 
}

Command* CommandParser::ParseCommand(const base::StringPiece& string) {
 return nullptr;
}

bool CommandParser::Expect(Token tok) {
 return false;
}

void CommandParser::Advance() {
 
}

}