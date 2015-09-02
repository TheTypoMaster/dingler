// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KERNEL_CONTAINER_CONTAINER_COMMAND_H__
#define KERNEL_CONTAINER_CONTAINER_COMMAND_H__

#include "base/basictypes.h"
#include "kernel/container_host/container_args.h"

namespace kernel {

class ContainerCommand {
public:

 enum class Code {
  // 000 Sys family
  // 100 - Container Family
  CONTAINER_CREATE = 100,
  CONTAINER_DROP = 101,
  CONTAINER_LOAD = 102,
  CONTAINER_UNLOAD = 103,
  CONTAINER_START = 104,
  CONTAINER_STOP = 105,
  CONTAINER_GETINFO = 106,
  CONTAINER_LIST = 107,
  // 200 - Process Family
  PROCESS_RUN = 200,
  PROCESS_KILL = 201,
  PROCESS_LIST = 202,
 };

 ContainerCommand(Code code, const ContainerArgs& args);
 ~ContainerCommand();

 Code code() const { return code_; }

 const ContainerArgs& args() const { return args_; }

private:
 
 Code  code_;
 
 const ContainerArgs& args_;
 
 DISALLOW_COPY_AND_ASSIGN(ContainerCommand);
};

}

#endif