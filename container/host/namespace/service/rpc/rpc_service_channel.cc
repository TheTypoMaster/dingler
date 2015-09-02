// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/service/rpc/rpc_service_channel.h"

#include "container/host/namespace/io/rpc_server_socket.h"

namespace container {

RPCServiceChannel::RPCServiceChannel(RPCServerSocket* socket): ServiceChannel(socket) {

}

RPCServiceChannel::~RPCServiceChannel() {

}

}