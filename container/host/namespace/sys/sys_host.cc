// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/sys/sys_host.h"

namespace container {

SysHost::SysHost(UUID id) : Resource(id, ResourceType::Sys) {

}

SysHost::~SysHost() {

}

}