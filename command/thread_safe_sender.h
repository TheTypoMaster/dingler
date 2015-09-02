// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMAND_THREAD_SAFE_SENDER_H__
#define COMMAND_THREAD_SAFE_SENDER_H__

#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"
#include "ipc/ipc_sender.h"

namespace base {
class SingleThreadTaskRunner;
}

namespace IPC {
class SyncMessageFilter;
}

namespace command {
class CommandThread;

// The class of Sender returned by ChildThread::thread_safe_sender().
class ThreadSafeSender
    : public IPC::Sender,
      public base::RefCountedThreadSafe<ThreadSafeSender> {
 public:
  bool Send(IPC::Message* msg) override;

 private:
  friend class CommandThread;  // for construction
  friend class base::RefCountedThreadSafe<ThreadSafeSender>;

  ThreadSafeSender(const scoped_refptr<base::SingleThreadTaskRunner>& main_task_runner,
                   const scoped_refptr<IPC::SyncMessageFilter>& sync_filter);
  ~ThreadSafeSender() override;

  scoped_refptr<base::SingleThreadTaskRunner> main_task_runner_;
  scoped_refptr<IPC::SyncMessageFilter> sync_filter_;

  DISALLOW_COPY_AND_ASSIGN(ThreadSafeSender);
};

}  // namespace command

#endif  // COMMAND_COMMON_THREAD_SAFE_SENDER_H_
