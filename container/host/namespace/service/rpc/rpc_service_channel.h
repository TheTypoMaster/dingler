// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_SERVICE_RPC_SERVICE_CHANNEL_H__
#define CONTAINER_HOST_NAMESPACE_SERVICE_RPC_SERVICE_CHANNEL_H__

#include "container/host/namespace/service/service_channel.h"

namespace container {
class RPCServerSocket;

class RPCServiceChannel : public ServiceChannel {
public:
 RPCServiceChannel(RPCServerSocket* socket);
 ~RPCServiceChannel() override;

private:

};

}

#endif