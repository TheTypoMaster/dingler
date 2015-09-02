// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "command/connection.h"

namespace command {

Connection::Connection(ConnectionType type): type_(type) {

}

Connection::~Connection(){

}

bool Connection::Open(const std::string& url) {
 return false;
}

void Connection::Close() {

}

}