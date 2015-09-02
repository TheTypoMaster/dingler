// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/io/http_server_socket.h"

namespace container {

HTTPServerSocket::HTTPServerSocket(UUID id) :
 ServerSocket(id, ServerSocketType::HTTP) {

}

HTTPServerSocket::~HTTPServerSocket() {

}

}