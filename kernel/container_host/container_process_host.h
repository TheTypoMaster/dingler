// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KERNEL_CONTAINER_HOST_CONTAINER_PROCESS_HOST_H__
#define KERNEL_CONTAINER_HOST_CONTAINER_PROCESS_HOST_H__

#include "base/basictypes.h"
#include "ipc/ipc_sender.h"
#include "ipc/ipc_listener.h"
#include "kernel/child_process_launcher.h"

namespace kernel {

class ContainerProcessHost : public IPC::Sender,
                             public IPC::Listener,
                             public ChildProcessLauncher::Client {
public:
 ContainerProcessHost();
 ~ContainerProcessHost() override;
  
 base::ProcessHandle GetHandle() const;

 // Sender
 bool Send(IPC::Message* msg) override;

 // ChildProcessLauncher
 void OnProcessLaunched() override;
 void OnProcessLaunchFailed() override;

private:

 bool OnMessageReceived(const IPC::Message& message) override;
 void OnChannelConnected(int32 peer_pid) override;
 void OnChannelError() override;
 void OnBadMessageReceived(const IPC::Message& message) override;

  DISALLOW_COPY_AND_ASSIGN(ContainerProcessHost);
};

}

#endif
