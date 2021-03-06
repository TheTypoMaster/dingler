// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/process/process.h"

#include "container/host/namespace/credential/auth_token.h"

namespace container {

Process::Process(UUID uuid) : Resource(uuid, ResourceType::Process) {}

Process::~Process() {}

}