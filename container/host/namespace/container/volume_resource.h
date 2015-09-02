// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_CONTAINER_VOLUME_RESOURCE_H__
#define CONTAINER_HOST_NAMESPACE_CONTAINER_VOLUME_RESOURCE_H__

#include "container/host/namespace/resource.h"

namespace container {

// represents a volume of a given container(in sys namespace)

class VolumeResource : public Resource {
public:
 VolumeResource(UUID id);
 ~VolumeResource() override;
private:
 
};

}

#endif