// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_SERVICE_RPC_SERVICE_API_H__
#define CONTAINER_HOST_NAMESPACE_SERVICE_RPC_SERVICE_API_H__

#include "container/host/namespace/service/service_api.h"

namespace container {

class RPCServiceApi : public ServiceApi {
public:
 RPCServiceApi(UUID id);
 ~RPCServiceApi() override;

private:
 DISALLOW_COPY_AND_ASSIGN(RPCServiceApi);
};

}

#endif