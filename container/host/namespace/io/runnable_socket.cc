// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/io/runnable_socket.h"

namespace container {

RunnableSocket::RunnableSocket(UUID id) : Socket(id, SocketType::RUNNABLE) {

}

RunnableSocket::~RunnableSocket() {

}

}