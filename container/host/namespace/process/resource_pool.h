// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_PROCESS_RESOURCE_POOL_H__
#define CONTAINER_HOST_NAMESPACE_PROCESS_RESOURCE_POOL_H__

#include "base/basictypes.h"

namespace container {
 /*
  * A list of Resources a given process is consuming
  */
class ResourcePool {
public:
 ResourcePool();
 ~ResourcePool();
private:
 DISALLOW_COPY_AND_ASSIGN(ResourcePool);
};
}

#endif