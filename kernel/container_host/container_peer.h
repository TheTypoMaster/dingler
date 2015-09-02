// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KERNEL_CONTAINER_CONTAINER_PEER_H__
#define KERNEL_CONTAINER_CONTAINER_PEER_H__

#include "base/basictypes.h"
#include "common/container_info.h"

namespace kernel {

// Represents a external container peer
// in contrast with ContainerHost = us
class ContainerPeer {
public:
 ContainerPeer();
 ~ContainerPeer();

private:

 DISALLOW_COPY_AND_ASSIGN(ContainerPeer);
};

}

#endif