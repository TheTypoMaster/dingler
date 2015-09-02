// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "kernel/command_host/command_process_host.h"

#include "common/child_process_host.h"
#include "common/child_process_messages.h"
#include "common/result_code.h"
#include "kernel/kernel_thread.h"
#include "kernel/kernel_message_filter.h"
#include "common/command_messages.h"
#include "common/paths.h"
#if defined(OS_WIN)
#include "ipc/attachment_broker_win.h"
#endif

namespace kernel {

CommandProcessHost::CommandProcessHost():
 id_(common::ChildProcessHost::GenerateChildProcessUniqueId()),
 weak_factory_(this) {

}

CommandProcessHost::~CommandProcessHost() {
 channel_.reset();
}

bool CommandProcessHost::Init() {
 //base::FilePath path;
 if (channel_)
  return true;

 //common::GetDefaultRootDirectory(&path);

 // Setup the IPC channel.
 // const std::string channel_id =
 //   IPC::Channel::GenerateVerifiedChannelID(std::string());

 IPC::ChannelHandle channel_id("command");

#if defined(OS_WIN)
 attachment_broker_.reset(new IPC::AttachmentBrokerWin());
#endif

 //base::ThreadRestrictions::SetIOAllowed(true);
 // we are opening a named socket here so temporaly
 // down the io restriction (fast operation and we are being called async anyway)
 // create channel
 scoped_refptr<base::SingleThreadTaskRunner> runner =
  KernelThread::GetMessageLoopProxyForThread(KernelThread::IO);

 channel_ = IPC::ChannelProxy::Create(
  channel_id, IPC::Channel::MODE_NAMED_SERVER, this, runner.get());
 // now we can lift it up again
 //base::ThreadRestrictions::SetIOAllowed(false);

 CreateMessageFilters();

 return true;
}

void CommandProcessHost::AddRoute(int32 routing_id, IPC::Listener* listener) {
 listeners_.AddWithID(listener, routing_id);
}

void CommandProcessHost::RemoveRoute(int32 routing_id) {
 listeners_.Remove(routing_id);
 Cleanup();
}

int CommandProcessHost::GetID() const {
 return id_;
}

base::ProcessHandle CommandProcessHost::GetHandle() const {
 return base::kNullProcessHandle;
}

bool CommandProcessHost::HasConnection() const {
 return channel_.get() != NULL;
}

void CommandProcessHost::Cleanup() {
 if (listeners_.IsEmpty()) {
  base::MessageLoop::current()->DeleteSoon(FROM_HERE, this);
  channel_.reset();
 }
}

IPC::ChannelProxy* CommandProcessHost::GetChannelProxy() {
 return channel_.get();
}

bool CommandProcessHost::Shutdown(int exit_code, bool wait) {
 return false;
}

void CommandProcessHost::OnProcessLaunched() {

}

void CommandProcessHost::OnProcessLaunchFailed() {

}

bool CommandProcessHost::Send(IPC::Message* msg) {
 return channel_->Send(msg);
}

bool CommandProcessHost::OnMessageReceived(const IPC::Message& msg) {
 if (msg.routing_id() == MSG_ROUTING_CONTROL) {
  // Dispatch control messages.
  IPC_BEGIN_MESSAGE_MAP(CommandProcessHost, msg)
   IPC_MESSAGE_HANDLER(ChildProcessHostMsg_ShutdownRequest,
   OnShutdownRequest)
   IPC_MESSAGE_HANDLER(CommandHostMsg_HelloReply,
   OnHelloReply)
   IPC_END_MESSAGE_MAP()

   return true;
 }

 IPC::Listener* listener = listeners_.Lookup(msg.routing_id());
 if (!listener) {
  if (msg.is_sync()) {
   // The listener has gone away, so we must respond or else the caller will
   // hang waiting for a reply.
   IPC::Message* reply = IPC::SyncMessage::GenerateReply(&msg);
   reply->set_reply_error();
   Send(reply);
  }
  return true;
 }
 return listener->OnMessageReceived(msg);
}

void CommandProcessHost::OnChannelConnected(int32 peer_pid) {
 LOG(INFO) << "channel connected.";
  base::MessageLoop::current()->PostDelayedTask(
      FROM_HERE,
      base::Bind(&CommandProcessHost::SendHello,
                 weak_factory_.GetWeakPtr()),
      base::TimeDelta::FromSeconds(10));
}

void CommandProcessHost::OnChannelError() {
 LOG(INFO) << "channel error.";
 ProcessDied(true);
}

void CommandProcessHost::OnBadMessageReceived(const IPC::Message& message) {
 LOG(ERROR) << "bad message " << message.type() << " terminating console.";
 Shutdown(common::RESULT_CODE_KILLED_BAD_MESSAGE, false);
}

// Creates and adds the IO thread message filters.
void CommandProcessHost::CreateMessageFilters() {

}

void CommandProcessHost::OnShutdownRequest() {
 Send(new ChildProcessMsg_Shutdown());
}

void CommandProcessHost::OnHelloReply() {
 base::MessageLoop::current()->PostDelayedTask(
  FROM_HERE,
  base::Bind(&CommandProcessHost::SendHello,
  weak_factory_.GetWeakPtr()),
  base::TimeDelta::FromSeconds(10));
}

void CommandProcessHost::SendHello() {
 Send(new CommandMsg_Hello);
}

// Handle termination of our process.
void CommandProcessHost::ProcessDied(bool already_dead) {

}

}