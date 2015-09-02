// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/service/rpc/rpc_service.h"

#include "container/host/namespace/service/rpc/rpc_service_channel.h"
#include "container/host/namespace/io/rpc_server_socket.h"
#include "container/common/uuid.h"

namespace container {

RPCService::RPCService(UUID id) :
 Service(id, ServiceType::RPC){

}

RPCService::~RPCService() {

}

void RPCService::Init() {
 auto sock = new RPCServerSocket(GenerateUUID());
 channel_.reset(new RPCServiceChannel(sock));

 state_ = ServiceState::Initialized;
}

void RPCService::Shutdown() {
 state_ = ServiceState::Shutdown;
}


}