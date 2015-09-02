// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_CONTAINER_CONTAINER_POOL_H__
#define CONTAINER_HOST_NAMESPACE_CONTAINER_CONTAINER_POOL_H__

#include "container/host/namespace/resource.h"

namespace container {

 // A resource representing the container pool

class ContainerPoolResource : public Resource {
public:
 ContainerPoolResource(UUID id);
 ~ContainerPoolResource() override;

private:

};

}

#endif