// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_SYS_SYS_HOST_H__
#define CONTAINER_HOST_NAMESPACE_SYS_SYS_HOST_H__

#include "container/host/namespace/resource.h"

namespace container {

// A resource representing the host os we are in
// things like: os flavor(windows, linux),
// screen size, dpi, etc..

class SysHost : public Resource {
public:
 SysHost(UUID id);
 ~SysHost() override;
private:

};

}

#endif