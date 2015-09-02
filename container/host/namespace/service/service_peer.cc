// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/service/service_peer.h"

namespace container {

ServicePeer::ServicePeer(UUID id): 
 Resource(id, ResourceType::Service) {

}

ServicePeer::~ServicePeer() {

}

}