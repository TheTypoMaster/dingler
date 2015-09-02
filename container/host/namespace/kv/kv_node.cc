// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/kv/kv_node.h"

namespace container {

KVNode::KVNode(UUID id): Resource(id, ResourceType::KV) {

}

KVNode::~KVNode() {

}

}