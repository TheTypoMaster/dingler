// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/io/dingler_peer.h"

namespace container {

DinglerPeer::DinglerPeer(UUID id) : Resource(id, ResourceType::IO) {

}

DinglerPeer::~DinglerPeer() {
 
}

}