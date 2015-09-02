// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/service/service_channel.h"

#include "container/host/namespace/io/server_socket.h"

namespace container {

ServiceChannel::ServiceChannel(ServerSocket* socket): socket_(socket) {

}

ServiceChannel::~ServiceChannel() {

}

bool ServiceChannel::Bind() {
 return false;
}

bool ServiceChannel::Listen() {
 return false;
}

void ServiceChannel::Close() {

}

}