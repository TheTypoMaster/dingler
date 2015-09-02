// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMAND_COMMAND_PARSER_H__
#define COMMAND_COMMAND_PARSER_H__

#include "base/basictypes.h"
#include "base/strings/string_piece.h"
#include "command/command_token.h"

namespace command {
struct Command;
// parser + lexer
class CommandParser {
public:
 CommandParser();
 ~CommandParser();

 Command* ParseCommand(const base::StringPiece& string);

private:

 bool Expect(Token tok);
 void Advance();

 DISALLOW_COPY_AND_ASSIGN(CommandParser);
};

}

#endif