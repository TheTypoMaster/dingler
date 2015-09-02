// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/io/bt_socket.h"

namespace container {

BTSocket::BTSocket(UUID id) : Socket(id, SocketType::BT) {

}

BTSocket::~BTSocket() {

}

}