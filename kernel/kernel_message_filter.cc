// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "kernel/kernel_message_filter.h"

#include "base/bind.h"
#include "base/bind_helpers.h"
#include "base/command_line.h"
#include "base/logging.h"
#include "base/process/kill.h"
#include "base/process/process_handle.h"
#include "base/task_runner.h"
#include "kernel/kernel_child_process_host.h"
//#include "kernel/user_metrics.h"
#include "common/result_code.h"
#include "ipc/ipc_sync_message.h"
#include "ipc/message_filter.h"

namespace kernel {

class KernelMessageFilter::Internal : public IPC::MessageFilter {
 public:
  explicit Internal(KernelMessageFilter* filter) : filter_(filter) {}

 private:
  ~Internal() override {}

  // IPC::MessageFilter implementation:
  void OnFilterAdded(IPC::Sender* sender) override {
    filter_->sender_ = sender;
    filter_->OnFilterAdded(sender);
  }

  void OnFilterRemoved() override { filter_->OnFilterRemoved(); }

  void OnChannelClosing() override {
   filter_->sender_ = NULL;
   filter_->OnChannelClosing();
  }

  void OnChannelConnected(int32 peer_pid) override {
   filter_->peer_process_ = base::Process::OpenWithExtraPrivileges(peer_pid);
   filter_->OnChannelConnected(peer_pid);
  }

  bool OnMessageReceived(const IPC::Message& message) override {
   KernelThread::ID thread = KernelThread::IO;
    filter_->OverrideThreadForMessage(message, &thread);

    if (thread == KernelThread::IO) {
      scoped_refptr<base::TaskRunner> runner =
          filter_->OverrideTaskRunnerForMessage(message);
      if (runner.get()) {
        runner->PostTask(
            FROM_HERE,
            base::Bind(
                base::IgnoreResult(&Internal::DispatchMessage), this, message));
        return true;
      }
      return DispatchMessage(message);
    }

    if (thread == KernelThread::MAIN &&
     !KernelMessageFilter::CheckCanDispatchOnMAIN(message, filter_.get())) {
      return true;
    }

    KernelThread::PostTask(
        thread, FROM_HERE,
        base::Bind(
            base::IgnoreResult(&Internal::DispatchMessage), this, message));
    return true;
  }

  bool GetSupportedMessageClasses(
      std::vector<uint32>* supported_message_classes) const override {
    supported_message_classes->assign(
        filter_->message_classes_to_filter().begin(),
        filter_->message_classes_to_filter().end());
    return true;
  }

  // Dispatches a message to the derived class.
  bool DispatchMessage(const IPC::Message& message) {
    bool rv = filter_->OnMessageReceived(message);
    DCHECK(KernelThread::CurrentlyOn(KernelThread::IO) || rv) <<
        "Must handle messages that were dispatched to another thread!";
    return rv;
  }

  scoped_refptr<KernelMessageFilter> filter_;

  DISALLOW_COPY_AND_ASSIGN(Internal);
};

KernelMessageFilter::KernelMessageFilter(uint32 message_class_to_filter)
    : internal_(NULL),
      sender_(NULL),
      message_classes_to_filter_(1, message_class_to_filter) {}

KernelMessageFilter::KernelMessageFilter(
    const uint32* message_classes_to_filter,
    size_t num_message_classes_to_filter)
    : internal_(NULL),
      sender_(NULL),
      message_classes_to_filter_(
          message_classes_to_filter,
          message_classes_to_filter + num_message_classes_to_filter) {
  DCHECK(num_message_classes_to_filter);
}

base::ProcessHandle KernelMessageFilter::PeerHandle() {
 return peer_process_.Handle();
}


void KernelMessageFilter::OnDestruct() const {
  delete this;
}

bool KernelMessageFilter::Send(IPC::Message* message) {
  if (message->is_sync()) {
    // We don't support sending synchronous messages from the browser.  If we
    // really needed it, we can make this class derive from SyncMessageFilter
    // but it seems better to not allow sending synchronous messages from the
    // browser, since it might allow a corrupt/malicious renderer to hang us.
    NOTREACHED() << "Can't send sync message through ShellMessageFilter!";
    return false;
  }

  if (!KernelThread::CurrentlyOn(KernelThread::IO)) {
   KernelThread::PostTask(
    KernelThread::IO,
        FROM_HERE,
        base::Bind(base::IgnoreResult(&KernelMessageFilter::Send), this,
                   message));
    return true;
  }

  if (sender_)
    return sender_->Send(message);

  delete message;
  return false;
}

base::TaskRunner* KernelMessageFilter::OverrideTaskRunnerForMessage(
    const IPC::Message& message) {
  return NULL;
}

bool KernelMessageFilter::CheckCanDispatchOnMAIN(const IPC::Message& message,
                                                 IPC::Sender* sender) {
#if defined(OS_WIN)
  // On Windows there's a potential deadlock with sync messsages going in
  // a circle from browser -> plugin -> renderer -> browser.
  // On Linux we can avoid this by avoiding sync messages from browser->plugin.
  // On Mac we avoid this by not supporting windowed plugins.
  if (message.is_sync() && !message.is_caller_pumping_messages()) {
    // NOTE: IF YOU HIT THIS ASSERT, THE SOLUTION IS ALMOST NEVER TO RUN A
    // NESTED MESSAGE LOOP IN THE RENDERER!!!
    // That introduces reentrancy which causes hard to track bugs.  You should
    // find a way to either turn this into an asynchronous message, or one
    // that can be answered on the IO thread.
    NOTREACHED() << "Can't send sync messages to MAIN thread without pumping "
        "messages in the renderer or else deadlocks can occur if the page "
        "has windowed plugins! (message type " << message.type() << ")";
    IPC::Message* reply = IPC::SyncMessage::GenerateReply(&message);
    reply->set_reply_error();
    sender->Send(reply);
    return false;
  }
#endif
  return true;
}

void KernelMessageFilter::BadMessageReceived() {
 peer_process_.Terminate(common::RESULT_CODE_KILLED_BAD_MESSAGE,
  false);
}

KernelMessageFilter::~KernelMessageFilter() {

}

IPC::MessageFilter* KernelMessageFilter::GetFilter() {
  // We create this on demand so that if a filter is used in a unit test but
  // never attached to a channel, we don't leak Internal and this;
  DCHECK(!internal_) << "Should only be called once.";
  internal_ = new Internal(this);
  return internal_;
}

}  // namespace kernel
