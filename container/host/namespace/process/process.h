// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_PROCESS_PROCESS_H__
#define CONTAINER_HOST_NAMESPACE_PROCESS_PROCESS_H__

#include "base/memory/scoped_ptr.h"
#include "container/host/namespace/resource.h"
#include "container/host/namespace/process/resource_pool.h"

namespace container {
class AuthToken;

class Process : public Resource {
public:
 Process(UUID id);
 ~Process() override;
 // the list of (opened) resources this process is using
 // in its lifetime
 ResourcePool* resource_pool() { return &resource_pool_; }

 // the auth token associated with this process
 AuthToken* auth_token() const { return auth_token_.get(); }

private:

 scoped_ptr<AuthToken> auth_token_;

 ResourcePool resource_pool_;

 DISALLOW_COPY_AND_ASSIGN(Process);
};

}

#endif