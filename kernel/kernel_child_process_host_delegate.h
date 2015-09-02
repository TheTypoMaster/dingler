// Copyright 2013 The Chromium Authors. All rights reserved.
// Copyright (c) 2015 Stripes. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KERNEL_KERNEL_CHILD_PROCESS_HOST_DELEGATE_H_
#define KERNEL_KERNEL_CHILD_PROCESS_HOST_DELEGATE_H_

#include "ipc/ipc_listener.h"

namespace kernel {

// Interface that all users of ShellChildProcessHost need to provide.
class KernelChildProcessHostDelegate : public IPC::Listener {
 public:
  ~KernelChildProcessHostDelegate() override {}

  // Delegates return true if it's ok to shut down the child process (which is
  // the default return value). The exception is if the host is in the middle of
  // sending a request to the process, in which case the other side might think
  // it's ok to shutdown, when really it's not.
  virtual bool CanShutdown() { return true; }

  // Called when the process has been started.
  virtual void OnProcessLaunched() {}

  // Called if the process failed to launch.  In this case the process never
  // started so there is no available exit code.
  virtual void OnProcessLaunchFailed() {}

  // Called if the process crashed. |exit_code| is the status returned when the
  // process crashed (for posix, as returned from waitpid(), for Windows, as
  // returned from GetExitCodeProcess()).
  virtual void OnProcessCrashed(int exit_code) {}
};

}

#endif