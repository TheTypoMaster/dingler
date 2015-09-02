// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMAND_COMMAND_AST_H__
#define COMMAND_COMMAND_AST_H__

#include "command/command_token.h"

namespace command {

struct Node {
 Token tok;
};

// a imperative statement (console, container, help, image, etc..)
struct Command : Node {

};

struct InvalidCommand : Command {

};

struct ConsoleCommand : Command {

};

struct ContainerCommand : Command {

};

struct HelpCommand : Command {

};

struct ImageCommand : Command {

};

struct ProcessCommand : Command {

};

struct QueryCommand : Command {

};

}

#endif
