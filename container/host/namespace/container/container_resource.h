// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_CONTAINER_CONTAINER_NODE_H__
#define CONTAINER_HOST_NAMESPACE_CONTAINER_CONTAINER_NODE_H__

#include "container/host/namespace/resource.h"

namespace container {

// A resource representing a container
// name, uuid, properties, etc

class ContainerResource : public Resource {
public:
 ContainerResource(UUID id);
 ~ContainerResource() override;
private:

};

}

#endif