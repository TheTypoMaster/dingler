// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/sys/sys_memory.h"

namespace container {

SysMemory::SysMemory(UUID id) : Resource(id, ResourceType::Sys) {

}

SysMemory::~SysMemory() {

}

}