// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/io/server_socket.h"

namespace container {

ServerSocket::ServerSocket(UUID id,
 ServerSocketType socket_type) : Resource(id, ResourceType::IO),
 socket_type_(socket_type) {

}

ServerSocket::~ServerSocket() {

}

}