// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMON_MESSAGE_ROUTER_H_
#define COMMON_MESSAGE_ROUTER_H_

#include "base/basictypes.h"
#include "base/id_map.h"
#include "ipc/ipc_listener.h"
#include "ipc/ipc_sender.h"

namespace common {

class MessageRouter : public IPC::Listener,
                      public IPC::Sender {
public:
 MessageRouter();
 ~MessageRouter() override;

 // Implemented by subclasses to handle control messages
 virtual bool OnControlMessageReceived(const IPC::Message& msg);

 // IPC::Listener implementation:
 bool OnMessageReceived(const IPC::Message& msg) override;

 // Like OnMessageReceived, except it only handles routed messages.  Returns
 // true if the message was dispatched, or false if there was no listener for
 // that route id.
 virtual bool RouteMessage(const IPC::Message& msg);

 // IPC::Sender implementation:
 bool Send(IPC::Message* msg) override;

 // Called to add a listener for a particular message routing ID.
 // Returns true if succeeded.
 bool AddRoute(int32 routing_id, IPC::Listener* listener);

 // Called to remove a listener for a particular message routing ID.
 void RemoveRoute(int32 routing_id);

private:

 IDMap<IPC::Listener> routes_;

 DISALLOW_COPY_AND_ASSIGN(MessageRouter);
};

}

#endif
