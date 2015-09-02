// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_IO_SOCKET_H__
#define CONTAINER_HOST_NAMESPACE_IO_SOCKET_H__

#include "container/host/namespace/resource.h"

namespace container {

enum class SocketType {
 RUNNABLE,
 IPC,
 RPC,
 TCP,
 UDP,
 HTTP,
 HTTPS,
 DINGLER, // our own p2p net
 TOR,
 BT,
};

class Socket : public Resource {
public:
 virtual ~Socket() override;

 SocketType socket_type() const { return socket_type_; }

protected:
 
 Socket(UUID uuid, 
  SocketType socket_type);

private:
 
 SocketType  socket_type_;
};

}

#endif