// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/io/https_server_socket.h"

namespace container {

HTTPSServerSocket::HTTPSServerSocket(UUID id) : ServerSocket(id, ServerSocketType::HTTPS) {

}

HTTPSServerSocket::~HTTPSServerSocket() {

}

}