// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KERNEL_CHILD_PROCESS_LAUNCHER_H_
#define KERNEL_CHILD_PROCESS_LAUNCHER_H_

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/process/kill.h"
#include "base/process/launch.h"
#include "base/process/process.h"

namespace kernel {
class ProcessLauncherDelegate;
// Launches a process asynchronously and notifies the client of the process
// handle when it's available.  It's used to avoid blocking the calling thread
// on the OS since often it can take > 100 ms to create the process.
class ChildProcessLauncher {
 public:
  class Client {
   public:
    // Will be called on the thread that the ChildProcessLauncher was
    // constructed on.
    virtual void OnProcessLaunched() = 0;

    virtual void OnProcessLaunchFailed() {};

   protected:
    virtual ~Client() {}
  };

  // Launches the process asynchronously, calling the client when the result is
  // ready.  Deleting this object before the process is created is safe, since
  // the callback won't be called.  If the process is still running by the time
  // this object destructs, it will be terminated.
  // Takes ownership of cmd_line.
  ChildProcessLauncher(
      ProcessLauncherDelegate* delegate,
      base::CommandLine* cmd_line,
      int child_process_id,
      Client* client);
  ~ChildProcessLauncher();

  // True if the process is being launched and so the handle isn't available.
  bool IsStarting();

  // Getter for the process.  Only call after the process has started.
  const base::Process& GetProcess() const;

  // Call this when the child process exits to know what happened to it.
  // |known_dead| can be true if we already know the process is dead as it can
  // help the implemention figure the proper TerminationStatus.
  // On Linux, the use of |known_dead| is subtle and can be crucial if an
  // accurate status is important. With |known_dead| set to false, a dead
  // process could be seen as running. With |known_dead| set to true, the
  // process will be killed if it was still running. See ZygoteHostImpl for
  // more discussion of Linux implementation details.
  // |exit_code| is the exit code of the process if it exited (e.g. status from
  // waitpid if on posix, from GetExitCodeProcess on Windows). |exit_code| may
  // be NULL.
  base::TerminationStatus GetChildTerminationStatus(bool known_dead,
                                                    int* exit_code);

  // Changes whether the process runs in the background or not.  Only call
  // this after the process has started.
  void SetProcessBackgrounded(bool background);

  // Controls whether the child process should be terminated on browser
  // shutdown.
  void SetTerminateChildOnShutdown(bool terminate_on_shutdown);

 private:
  class Context;

  scoped_refptr<Context> context_;

  DISALLOW_COPY_AND_ASSIGN(ChildProcessLauncher);
};

}

#endif
