// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_CONTAINER_CLIENT_H__
#define CONTAINER_CONTAINER_CLIENT_H__

#include <vector>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/files/file_path.h"
#include "ipc/ipc_sender.h"
#include "ipc/ipc_listener.h"

namespace container {
class ContainerNavigator;

class ContainerClient : public IPC::Sender,
                        public IPC::Listener {
public:

 ContainerClient();
 ~ContainerClient() override;

 ContainerNavigator* CreateNavigator();

 // Sender overrides
 bool Send(IPC::Message* msg) override;

private:
 bool OnMessageReceived(const IPC::Message& message) override;
 void OnChannelConnected(int32 peer_pid) override;
 void OnChannelError() override;
 void OnBadMessageReceived(const IPC::Message& message) override;
  
 DISALLOW_COPY_AND_ASSIGN(ContainerClient);
};

}

#endif
