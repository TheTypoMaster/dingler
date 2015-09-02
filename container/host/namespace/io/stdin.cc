// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/io/stdin.h"

namespace container {

STDIN::STDIN(UUID id) : Resource(id, ResourceType::IO, SpecialMode::Singleton) {

}

STDIN::~STDIN() {

}

}