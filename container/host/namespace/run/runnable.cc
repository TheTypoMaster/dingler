// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/run/runnable.h"

namespace container {

Runnable::Runnable(UUID id): Resource(id, ResourceType::Run) {

}

Runnable::~Runnable() {

}

void Runnable::Run() {

}

}