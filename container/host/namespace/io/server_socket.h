// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_IO_SERVER_SOCKET_H__
#define CONTAINER_HOST_NAMESPACE_IO_SERVER_SOCKET_H__

#include "container/host/namespace/resource.h"

namespace container {

enum class ServerSocketType {
 IPC,
 RPC,
 TCP,
 UDP,
 HTTP,
 HTTPS
};

class ServerSocket : public Resource {
public:
 virtual ~ServerSocket() override;

 ServerSocketType socket_type() const { return socket_type_; }

protected:
 
 ServerSocket(UUID id,
  ServerSocketType socket_type);

private:
 
 ServerSocketType  socket_type_;
};

}

#endif