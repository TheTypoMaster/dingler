// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_SERVICE_SERVICE_CHANNEL_H__
#define CONTAINER_HOST_NAMESPACE_SERVICE_SERVICE_CHANNEL_H__

#include "base/memory/scoped_ptr.h"

namespace container {
class ServerSocket;

class ServiceChannel {
public:
 virtual ~ServiceChannel();

 ServerSocket* socket() const { return socket_.get(); }

 bool Bind();
 bool Listen();
 void Close();

protected:
 ServiceChannel(ServerSocket* socket);
private:

 scoped_ptr<ServerSocket> socket_;
};

}


#endif