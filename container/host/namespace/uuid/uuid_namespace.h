// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_UUID_CONTAINER_H__
#define CONTAINER_HOST_NAMESPACE_UUID_CONTAINER_H__

#include "container/host/namespace/namespace.h"

namespace container {

// Circunvent the address system to access resources
// by using only the uuid to find any existent resource
// in the container independent of the filesystem its in
class UUIDNamespace : public Namespace {
public:
 UUIDNamespace(UUID id);
 ~UUIDNamespace() override;

private:

};

}

#endif