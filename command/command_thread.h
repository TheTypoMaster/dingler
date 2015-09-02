// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMAND_COMMAND_THREAD_H__
#define COMMAND_COMMAND_THREAD_H__

#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/shared_memory.h"
#include "base/memory/weak_ptr.h"
#include "base/memory/ref_counted.h"
#include "base/message_loop/message_loop.h"
#include "base/synchronization/waitable_event.h"
#include "base/threading/thread.h"
#include "base/tracked_objects.h"
#include "ipc/ipc_sender.h"
#include "ipc/ipc_listener.h"
#include "common/message_router.h"

namespace IPC {
class Channel;
struct ChannelHandle;
class SyncChannel;
class SyncMessageFilter;
class MessageFilter;
}  // namespace IPC

namespace command {
class Screen;
class Console;
class ThreadSafeSender;
class CommandExecutor;


class CommandThread : public IPC::Sender,
                      public IPC::Listener {
public:

 static CommandThread* current();

 CommandThread();
 explicit CommandThread(scoped_ptr<base::MessageLoop> cmd_message_loop);
 ~CommandThread() override;
 
 void Shutdown();
 // IPC::Sender implementation:
 bool Send(IPC::Message* msg) override;

 IPC::SyncChannel* channel() { return channel_.get(); }

 common::MessageRouter* GetRouter();

 base::MessageLoop* message_loop() const { return main_message_loop_.get(); }

 CommandExecutor* command_executor() const { return executor_.get(); }

 ThreadSafeSender* thread_safe_sender() const {
  return thread_safe_sender_.get();
 }

 void AddRoute(int32 routing_id, IPC::Listener* listener);
 void RemoveRoute(int32 routing_id);
 int GenerateRoutingID();

 void AddFilter(IPC::MessageFilter* filter);
 void RemoveFilter(IPC::MessageFilter* filter);

 base::WaitableEvent* GetShutdownEvent();

private:
 friend class Console;

 class CommandThreadMessageRouter : public common::MessageRouter {
 public:
  // |sender| must outlive this object.
  explicit CommandThreadMessageRouter(IPC::Sender* sender);
  bool Send(IPC::Message* msg) override;
 private:
  IPC::Sender* const sender_;
 };

 void Init(std::string channel_name);

 void OnProcessFinalRelease();

 virtual bool OnControlMessageReceived(const IPC::Message& msg);

 // IPC::Listener implementation:
 bool OnMessageReceived(const IPC::Message& msg) override;
 void OnChannelConnected(int32 peer_pid) override;
 void OnChannelError() override;

 // IPC message handlers.
 void OnShutdown();
 void OnChannelEstablished(IPC::ChannelHandle handle);
 void OnHello();

 void ReadOnReaderThread();
 void EvalOnReaderThread(char* text, int len);

 void SendHello();

 void EnsureConnected();

 std::string channel_name_;

 //base::MessageLoopProxy* io_message_loop_proxy_;

 // Allows threads other than the main thread to send sync messages.
 scoped_refptr<IPC::SyncMessageFilter> sync_message_filter_;

 scoped_refptr<ThreadSafeSender> thread_safe_sender_;

 CommandThreadMessageRouter router_;

 scoped_ptr<base::MessageLoop> main_message_loop_;

 // The channel from the Terminal process to the kernel process.
 scoped_ptr<IPC::SyncChannel> channel_;

 scoped_ptr<CommandExecutor> executor_;

 bool channel_error_;

 //char* text_;
 //size_t textlen_;
 // managed by Terminal
 Screen* screen_;

 base::WeakPtrFactory<CommandThread> weak_factory_;

 DISALLOW_COPY_AND_ASSIGN(CommandThread);
};

}

#endif