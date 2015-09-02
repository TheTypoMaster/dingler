// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_SERVICE_SERVICE_PEER_H__
#define CONTAINER_HOST_NAMESPACE_SERVICE_SERVICE_PEER_H__

#include "container/host/namespace/resource.h"

namespace container {

 /*
  * A peer (in a service network) sharing or consuming a service
  */
class ServicePeer : public Resource {
public:
 ServicePeer(UUID id);
 ~ServicePeer() override;
private:

};

}

#endif
