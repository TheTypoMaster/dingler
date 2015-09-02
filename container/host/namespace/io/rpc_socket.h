// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_IO_RPC_SOCKET_H__
#define CONTAINER_HOST_NAMESPACE_IO_RPC_SOCKET_H__

#include "container/host/namespace/io/socket.h"

namespace container {

class RPCSocket : public Socket {
public:
 RPCSocket(UUID id);
 ~RPCSocket() override;

private:

};

}

#endif
