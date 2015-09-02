// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_IO_CONTAINER_H__
#define CONTAINER_HOST_NAMESPACE_IO_CONTAINER_H__

#include "container/host/namespace/namespace.h"

namespace container {

// io: Input, Output, IPC, Net(TCP, UDP), etc..
// everything IO
class IONamespace : public Namespace {
public:
 IONamespace(UUID id);
 ~IONamespace() override;

private:

};

}

#endif