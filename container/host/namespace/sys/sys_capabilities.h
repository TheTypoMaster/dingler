// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_SYS_SYS_CAPABILITIES_H__
#define CONTAINER_HOST_NAMESPACE_SYS_SYS_CAPABILITIES_H__

#include "container/host/namespace/resource.h"

namespace container {

// A resource that will give us the capabilities 
// the container are allowed to use
// and the ones that are forbidden
//
class SysCapabilities : public Resource {
public:
 SysCapabilities(UUID id);
 ~SysCapabilities() override;
private:

};

}

#endif