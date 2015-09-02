// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_IO_DINGLER_PEER_H__
#define CONTAINER_HOST_NAMESPACE_IO_DINGLER_PEER_H__

#include "container/host/namespace/resource.h"

namespace container {
 /*
  * Represents another machine/peer within the dingler platform
  * a remote peer
  */
class DinglerPeer : public Resource {
public:
 DinglerPeer(UUID id);
 ~DinglerPeer() override;
private:

};

}

#endif