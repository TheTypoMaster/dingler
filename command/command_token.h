// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMAND_COMMAND_TOKEN_H__
#define COMMAND_COMMAND_TOKEN_H__

namespace command {

enum class Token {
 Comma,    // ,
 Linefeed, // \r
 // statements
 ConsoleCmd, // 'console'
 ContainerCmd,
 HelpCmd,
 ImageCmd,
 ProcessCmd,
 QueryCmd,
};

}

#endif