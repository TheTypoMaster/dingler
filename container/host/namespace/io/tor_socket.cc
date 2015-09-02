// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/io/tor_socket.h"

namespace container {

TORSocket::TORSocket(UUID id) : Socket(id, SocketType::TOR) {

}

TORSocket::~TORSocket() {

}

}