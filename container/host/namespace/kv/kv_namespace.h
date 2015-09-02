// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_KV_CONTAINER_H__
#define CONTAINER_HOST_NAMESPACE_KV_CONTAINER_H__

#include "container/host/namespace/namespace.h"

namespace container {

// A key-value store namespace

class KVNamespace : public Namespace {
public:
 KVNamespace(UUID uuid);
 ~KVNamespace() override;

private:

};

}

#endif