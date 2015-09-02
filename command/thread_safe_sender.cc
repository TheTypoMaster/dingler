// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Copyright (c) 2015 Stripes. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "command/thread_safe_sender.h"

#include "base/thread_task_runner_handle.h"
#include "command/command_thread.h"
#include "ipc/ipc_sync_message_filter.h"

namespace command {

ThreadSafeSender::ThreadSafeSender(
    const scoped_refptr<base::SingleThreadTaskRunner>& main_task_runner,
    const scoped_refptr<IPC::SyncMessageFilter>& sync_filter)
    : main_task_runner_(main_task_runner), sync_filter_(sync_filter) {
}

ThreadSafeSender::~ThreadSafeSender() {
 
}

bool ThreadSafeSender::Send(IPC::Message* msg) {
  if (main_task_runner_->BelongsToCurrentThread())
    return CommandThread::current()->Send(msg);
  return sync_filter_->Send(msg);
}

}  // namespace command
