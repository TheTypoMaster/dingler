// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMON_CHILD_PROCESS_HOST_DELEGATE_H_
#define COMMON_CHILD_PROCESS_HOST_DELEGATE_H_

#include <string>

#include "base/process/process.h"
#include "ipc/ipc_listener.h"

namespace common {

// Interface that all users of ChildProcessHost need to provide.
class ChildProcessHostDelegate : public IPC::Listener {
 public:
  ~ChildProcessHostDelegate() override {}

  // Delegates return true if it's ok to shut down the child process (which is
  // the default return value). The exception is if the host is in the middle of
  // sending a request to the process, in which case the other side might think
  // it's ok to shutdown, when really it's not.
  virtual bool CanShutdown();

  // Called when the child process unexpected closes the IPC channel. Delegates
  // would normally delete the object in this case.
  virtual void OnChildDisconnected() {}

  // Returns a reference to the child process. This can be called only after
  // OnProcessLaunched is called or it will be invalid and may crash.
  virtual const base::Process& GetProcess() const = 0;
};

};  // namespace stripes

#endif  // STRIPES_MODULES_COMMON_CHILD_PROCESS_HOST_DELEGATE_H_
