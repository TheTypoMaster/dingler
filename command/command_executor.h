// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMAND_COMMAND_EXECUTOR_H__
#define COMMAND_COMMAND_EXECUTOR_H__

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"

namespace command {
//class ScriptHost;

class CommandExecutor {
public:
 CommandExecutor();//ScriptHost* script_host);
 ~CommandExecutor();

 //ScriptHost* script_host() const { return script_host_; }

private:
 // owned by Terminal
 //ScriptHost* script_host_;

 DISALLOW_COPY_AND_ASSIGN(CommandExecutor);
};

}

#endif