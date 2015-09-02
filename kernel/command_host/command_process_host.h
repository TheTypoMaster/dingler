// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KERNEL_CONSOLE_HOST_COMMAND_PROCESS_HOST_H__
#define KERNEL_CONSOLE_HOST_COMMAND_PROCESS_HOST_H__

#include <map>
#include <string>

#include "base/basictypes.h"
#include "base/atomic_sequence_num.h"
#include "base/memory/scoped_ptr.h"
#include "base/id_map.h"
#include "base/observer_list.h"
#include "base/basictypes.h"
#include "ipc/ipc_sender.h"
#include "ipc/ipc_listener.h"
#include "ipc/ipc_channel_proxy.h"
#include "kernel/child_process_launcher.h"

namespace kernel {

class CommandProcessHost : public IPC::Sender,
                           public IPC::Listener,
                           public ChildProcessLauncher::Client {
public:
 CommandProcessHost();
 ~CommandProcessHost() override;

 bool Init();

 int GetID() const;
 base::ProcessHandle GetHandle() const;
 IPC::ChannelProxy* GetChannelProxy();
 bool HasConnection() const;

 void AddRoute(int32 routing_id, IPC::Listener* listener);
 void RemoveRoute(int32 routing_id);

 void Cleanup();
 bool Shutdown(int exit_code, bool wait);

 // Sender
 bool Send(IPC::Message* msg) override;

 // ChildProcessLauncher
 void OnProcessLaunched() override;
 void OnProcessLaunchFailed() override;
 
 // Receiver
 bool OnMessageReceived(const IPC::Message& message) override;
 void OnChannelConnected(int32 peer_pid) override;
 void OnChannelError() override;
 void OnBadMessageReceived(const IPC::Message& message) override;

private:

 // Creates and adds the IO thread message filters.
 void CreateMessageFilters();
 void SendHello();

 // message handlers
 void OnShutdownRequest();
 void OnHelloReply();
 

 // Handle termination of our process.
 void ProcessDied(bool already_dead);

 // The registered IPC listener objects. When this list is empty, we should
 // delete ourselves.
 IDMap<IPC::Listener> listeners_;

 // A proxy for our IPC::Channel that lives on the IO thread (see
 // shell_process.h)
 scoped_ptr<IPC::ChannelProxy> channel_;

 scoped_ptr<IPC::AttachmentBroker> attachment_broker_;

 //scoped_refptr<BundleMessageFilter> bundle_message_filter_;

 int id_;

 base::AtomicSequenceNumber next_routing_id_;

 base::WeakPtrFactory<CommandProcessHost> weak_factory_;

 DISALLOW_COPY_AND_ASSIGN(CommandProcessHost);
};

}

#endif