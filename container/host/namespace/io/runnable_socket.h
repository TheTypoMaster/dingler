// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_IO_RUNNABLE_SOCKET_H__
#define CONTAINER_HOST_NAMESPACE_IO_RUNNABLE_SOCKET_H__

#include "container/host/namespace/io/socket.h"

namespace container {
/*
 * Each application is associated with a app socket
 * which is the channel where the app receives and
 * send io events
 *
 * The IO events are more app related, like KILL
 */
class RunnableSocket : public Socket {
public:
 RunnableSocket(UUID id);
 ~RunnableSocket() override;

private:

};

}

#endif