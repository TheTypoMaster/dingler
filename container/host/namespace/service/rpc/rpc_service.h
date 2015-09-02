// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_SERVICE_RPC_SERVICE_H__
#define CONTAINER_HOST_NAMESPACE_SERVICE_RPC_SERVICE_H__

#include "container/host/namespace/service/service.h"

namespace container {
 /*
  * A service exposed by a container externally
  * the idea is that externally to a container
  * we can only interact with a container
  * through its service api
  *
  * This is backed up by a GRPC service
  */
class RPCService : public Service {
public:
 RPCService(UUID id);
 ~RPCService() override;

 void Init() override;
 void Shutdown() override;

private:

 DISALLOW_COPY_AND_ASSIGN(RPCService);
};

}

#endif