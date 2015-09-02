// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_NAMESPACE_SYS_CONTAINER_H__
#define CONTAINER_NAMESPACE_SYS_CONTAINER_H__

#include "container/host/namespace/namespace.h"

namespace container {

// sys: CPU, Memory, Capabilities, Hardware info, etc.. 
// machine state in general

class SysNamespace : public Namespace {
public:
 SysNamespace(UUID id);
 ~SysNamespace() override;

private:

};

}

#endif