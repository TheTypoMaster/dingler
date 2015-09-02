// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/service/rpc/rpc_service_api.h"

namespace container {

RPCServiceApi::RPCServiceApi(UUID id) : ServiceApi(id, ServiceApiType::RPC_API) {

}

RPCServiceApi::~RPCServiceApi() {

}

}