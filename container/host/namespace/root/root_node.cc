// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/root/root_node.h"

namespace container {

RootNode::RootNode(UUID id): 
 Resource(id, ResourceType::Root),
 visibility_(RootNodeVisibility::Private) {

}

RootNode::~RootNode() {

}

}