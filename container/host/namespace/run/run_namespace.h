// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_RUN_NAMESPACE_H__
#define CONTAINER_HOST_NAMESPACE_RUN_NAMESPACE_H__

#include "container/host/namespace/namespace.h"

namespace container {

class RunNamespace : public Namespace {
public:
 RunNamespace(UUID id);
 ~RunNamespace() override;

private:

};

}

#endif