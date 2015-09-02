// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "kernel/container_host/container_command.h"

namespace kernel {

ContainerCommand::ContainerCommand(Code code, const ContainerArgs& args): 
 code_(code), 
 args_(args) {

}

ContainerCommand::~ContainerCommand() {}

}