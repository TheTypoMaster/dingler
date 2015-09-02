// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_ROOT_CONTAINER_H__
#define CONTAINER_HOST_NAMESPACE_ROOT_CONTAINER_H__

#include "container/host/namespace/namespace.h"

namespace container {
// The topmost FS of each volume
class RootNamespace : public Namespace {
public:
 RootNamespace(UUID id);
 ~RootNamespace() override;

private:

};

}

#endif