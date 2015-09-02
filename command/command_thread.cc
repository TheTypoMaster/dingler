// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "command/command_thread.h"

#include "base/allocator/allocator_extension.h"
#include "base/base_switches.h"
#include "base/basictypes.h"
#include "base/command_line.h"
#include "base/debug/leak_annotations.h"
#include "base/lazy_instance.h"
#include "base/logging.h"
#include "base/message_loop/message_loop.h"
#include "base/message_loop/timer_slack.h"
#include "base/process/kill.h"
#include "base/process/process_handle.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/string_util.h"
#include "base/synchronization/condition_variable.h"
#include "base/synchronization/lock.h"
#include "base/threading/thread_local.h"
#include "base/tracked_objects.h"
#include "ipc/ipc_logging.h"
#include "ipc/ipc_switches.h"
#include "ipc/ipc_sync_channel.h"
#include "ipc/ipc_sync_message_filter.h"
#include "command/console.h"
#include "command/screen.h"
#include "command/key.h"
#include "command/command_executor.h"
#include "command/thread_safe_sender.h"
#include "common/command_messages.h"
#include "common/child_process_messages.h"

namespace command {

namespace {

// How long to wait for a connection to the browser process before giving up.
const int kConnectionTimeoutS = 15;

base::LazyInstance<base::ThreadLocalPointer<CommandThread> > g_lazy_tls =
 LAZY_INSTANCE_INITIALIZER;

} // namespace

CommandThread::CommandThreadMessageRouter::CommandThreadMessageRouter(
 IPC::Sender* sender)
 : sender_(sender) {}

bool CommandThread::CommandThreadMessageRouter::Send(IPC::Message* msg) {
 return sender_->Send(msg);
}


// static 
CommandThread* CommandThread::current() {
 return g_lazy_tls.Pointer()->Get();
}

CommandThread::CommandThread() : router_(this),
  channel_error_(false),
  weak_factory_(this){
  Init("command");
}

CommandThread::CommandThread(scoped_ptr<base::MessageLoop> main_message_loop)
 : router_(this),
 main_message_loop_(main_message_loop.Pass()),
 channel_error_(false),
 weak_factory_(this) {
 Init("command");
}


CommandThread::~CommandThread() {

}

void CommandThread::Init(std::string channel_name) {
 channel_name_ = std::move(channel_name);
 g_lazy_tls.Pointer()->Set(this);

 channel_ = IPC::SyncChannel::Create(channel_name_,
  IPC::Channel::MODE_NAMED_CLIENT,
  this,
  Console::Instance()->io_message_loop()->task_runner(),
  true, Console::Instance()->GetShutDownEvent());

 DCHECK(channel_.get()); // fatal if null

 sync_message_filter_ =
  new IPC::SyncMessageFilter(Console::Instance()->GetShutDownEvent());
 thread_safe_sender_ = new ThreadSafeSender(
     Console::Instance()->io_message_loop()->task_runner(), sync_message_filter_.get());
 channel_->AddFilter(sync_message_filter_.get());

 executor_.reset(new CommandExecutor);

 screen_ = Console::Instance()->current_screen();

 Console::Instance()->reader_message_loop()->PostTask(
  FROM_HERE,
  base::Bind(&CommandThread::ReadOnReaderThread,
  weak_factory_.GetWeakPtr()));

 /*int connection_timeout = kConnectionTimeoutS;
  base::MessageLoop::current()->PostDelayedTask(
     FROM_HERE,
     base::Bind(&CommandThread::EnsureConnected,
                weak_factory_.GetWeakPtr()),
                base::TimeDelta::FromSeconds(connection_timeout));*/
}

void CommandThread::Shutdown() {
 main_message_loop_.reset();
 channel_->RemoveFilter(sync_message_filter_.get());
 channel_->ClearIPCTaskRunner();
 g_lazy_tls.Pointer()->Set(nullptr);
}

void CommandThread::AddRoute(int32 routing_id, IPC::Listener* listener) {
 router_.AddRoute(routing_id, listener);
}

void CommandThread::RemoveRoute(int32 routing_id) {
 router_.RemoveRoute(routing_id);
}

int CommandThread::GenerateRoutingID() {
 int routing_id = MSG_ROUTING_NONE;
 //Send(new EngineHostMsg_GenerateRoutingID(&routing_id));
 return routing_id;
}

void CommandThread::AddFilter(IPC::MessageFilter* filter) {
 channel_->AddFilter(filter);
}

void CommandThread::RemoveFilter(IPC::MessageFilter* filter) {
 channel_->RemoveFilter(filter);
}

base::WaitableEvent* CommandThread::GetShutdownEvent() {
 return Console::Instance()->GetShutDownEvent();
}


bool CommandThread::Send(IPC::Message* msg) {
 DCHECK(base::MessageLoop::current() == message_loop());
 if (!channel_) {
  delete msg;
  return false;
 }

 return channel_->Send(msg);
}

common::MessageRouter* CommandThread::GetRouter() {
 DCHECK(base::MessageLoop::current() == message_loop());
 return &router_;
}

bool CommandThread::OnControlMessageReceived(const IPC::Message& msg) {
 return false;
}

bool CommandThread::OnMessageReceived(const IPC::Message& msg) {
 bool handled = true;

  IPC_BEGIN_MESSAGE_MAP(CommandThread, msg)
   IPC_MESSAGE_HANDLER(ChildProcessMsg_Shutdown, OnShutdown)
   IPC_MESSAGE_HANDLER(CommandMsg_Hello, OnHello)
   IPC_MESSAGE_UNHANDLED(handled = false)
   IPC_END_MESSAGE_MAP()

   if (handled)
    return true;

  if (msg.routing_id() == MSG_ROUTING_CONTROL)
   return OnControlMessageReceived(msg);

  return router_.OnMessageReceived(msg);
 }

void CommandThread::OnChannelConnected(int32 peer_pid) {
  LOG(INFO) << "CommandThread::OnChannelConnected";
  //weak_factory_.InvalidateWeakPtrs();
  screen_->ShowPrompt(false);
  screen_->PutString("Connected.");
  screen_->ShowPrompt(true);
  screen_->NewLine();
}

void CommandThread::OnChannelError() {
 // TODO: lan?ar um processo kernel caso de o channel error
  channel_error_ = true;
  screen_->ShowPrompt(false);
  screen_->PutString("Error: host process not found. launching..");
  screen_->ShowPrompt(true);
  screen_->NewLine();
}

void CommandThread::OnShutdown() {
 DCHECK(main_message_loop_.get());
 main_message_loop_->Quit();
}

void CommandThread::OnProcessFinalRelease() {
 if (channel_error_) {
  base::MessageLoop::current()->Quit();
  return;
}

 // The child process shutdown sequence is a request response based mechanism,
 // where we send out an initial feeler request to the child process host
 // instance in the browser to verify if it's ok to shutdown the child process.
 // The browser then sends back a response if it's ok to shutdown. This avoids
  // race conditions if the process refcount is 0 but there's an IPC message
  // inflight that would addref it.
  Send(new ChildProcessHostMsg_ShutdownRequest);
 }

void CommandThread::OnHello() {
 // todo: should check if screen its busy
 screen_->ShowPrompt(false);
 screen_->NewLine();
 screen_->PutString("Hello received from server");
 screen_->ShowPrompt(true);
 screen_->NewLine();
}

void CommandThread::ReadOnReaderThread() {

 for (;;) {
  char* line = nullptr;
  int len = screen_->ReadLine(&line);
  if (len > 0) {
   CommandThread::EvalOnReaderThread(line, len);
   free(line);
  }
  else { // just "reset" the screen
   screen_->NewLine();
  }
 }
}

void CommandThread::EvalOnReaderThread(char* text, int len) {
 screen_->ShowPrompt(false);
 screen_->NewLine();
 screen_->PutString(text);
 screen_->ShowPrompt(true);
 screen_->NewLine();
 /*if (memcmp(text, "hello", len) == 0) {
  message_loop()->PostTask(
   FROM_HERE,
   base::Bind(&CommandThread::SendHello,
   weak_factory_.GetWeakPtr()));
 }*/
}

void CommandThread::SendHello() {
 CommandThread::Send(new CommandHostMsg_HelloReply);
}

void CommandThread::EnsureConnected() {
 /*screen_->ShowPrompt(false);
 screen_->NewLine();
 screen_->PutString("Error: connection with host process timeout");
 screen_->ShowPrompt(true);
 screen_->NewLine();*/
}

} // namespace command
