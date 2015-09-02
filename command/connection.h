// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMAND_COMMAND_CONNECTION_H__
#define COMMAND_COMMAND_CONNECTION_H__

#include <string>

#include "base/basictypes.h"

namespace command {

enum class ConnectionType {
 IPC
};

class Connection {
public:
 Connection(ConnectionType type);
 ~Connection();

 bool Open(const std::string& url);
 void Close();

private:

 ConnectionType type_;

 DISALLOW_COPY_AND_ASSIGN(Connection);
};

}

#endif