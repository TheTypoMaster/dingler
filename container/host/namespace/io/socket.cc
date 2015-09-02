// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/io/socket.h"

namespace container {

Socket::Socket(UUID uuid,
 SocketType socket_type) : Resource(uuid, ResourceType::IO),
 socket_type_(socket_type) {

}

Socket::~Socket() {

}

}