// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_NAMESPACE_HOST_SYS_SYS_MEMORY_H__
#define CONTAINER_NAMESPACE_HOST_SYS_SYS_MEMORY_H__

#include "container/host/namespace/resource.h"

namespace container {

class SysMemory : public Resource {
public:
 SysMemory(UUID id);
 ~SysMemory() override;
private:

};

}

#endif