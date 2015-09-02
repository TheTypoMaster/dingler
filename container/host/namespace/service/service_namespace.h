// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_SERVICE_CONTAINER_H__
#define CONTAINER_HOST_NAMESPACE_SERVICE_CONTAINER_H__

#include "container/host/namespace/namespace.h"

namespace container {

class ServiceNamespace : public Namespace {
public:
 ServiceNamespace(UUID id);
 ~ServiceNamespace() override;

 // TODO: expose services functionalities here
 // like start, stop, list, etc

private:

};

}

#endif