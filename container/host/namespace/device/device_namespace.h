// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_DEVICE_DEVICE_NAMESPACE_H__
#define CONTAINER_HOST_NAMESPACE_DEVICE_DEVICE_NAMESPACE_H__

#include "container/host/namespace/namespace.h"

namespace container {

// mostly for hardware devices available to the container
class DeviceNamespace : public Namespace {
public:
 DeviceNamespace(UUID uuid);
 ~DeviceNamespace() override;

private:

};

}

#endif