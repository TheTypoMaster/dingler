// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DINGLER_KERNEL_PROCESS_SINGLETON_H_
#define DINGLER_KERNEL_PROCESS_SINGLETON_H_

#include "build/build_config.h"

#if defined(OS_WIN)
#include <windows.h>
#endif  // defined(OS_WIN)

#include <set>
#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/command_line.h"
#include "base/files/file_path.h"
#include "base/logging.h"
#include "base/memory/ref_counted.h"
#include "base/process/process.h"
#include "base/threading/non_thread_safe.h"

#if defined(OS_POSIX) && !defined(OS_ANDROID)
#include "base/files/scoped_temp_dir.h"
#endif

#if defined(OS_WIN)
#include "base/win/message_window.h"
#endif  // defined(OS_WIN)

namespace base {
class CommandLine;
}

namespace kernel {

// ProcessSingleton ----------------------------------------------------------
//
// This class allows different browser processes to communicate with
// each other.  It is named according to the user data directory, so
// we can be sure that no more than one copy of the application can be
// running at once with a given data directory.
//
// Implementation notes:
// - the Windows implementation uses an invisible global message window;
// - the Linux implementation uses a Unix domain socket in the user data dir.

class ProcessSingleton : public base::NonThreadSafe {
 public:
  enum NotifyResult {
    PROCESS_NONE,
    PROCESS_NOTIFIED,
    PROFILE_IN_USE,
    LOCK_ERROR,
  };

  // Implement this callback to handle notifications from other processes. The
  // callback will receive the command line and directory with which the other
  // Chrome process was launched. Return true if the command line will be
  // handled within the current browser instance or false if the remote process
  // should handle it (i.e., because the current process is shutting down).
  typedef base::Callback<bool(
      const base::CommandLine& command_line,
      const base::FilePath& current_directory)> NotificationCallback;

  // Provides a ProcessSingleton::NotificationCallback that can queue up
  // command-line invocations during startup and execute them when startup
  // completes.
  //
  // The object starts in a locked state. |Unlock()| must be called
  // when the process is prepared to handle command-line invocations.
  //
  // Once unlocked, notifications are forwarded to a wrapped NotificationCallback.
  class ProcessSingletonStartupLock : public base::NonThreadSafe {
  public:
   explicit ProcessSingletonStartupLock(
    const ProcessSingleton::NotificationCallback& original_callback);

   ~ProcessSingletonStartupLock();

   // Returns the ProcessSingleton::NotificationCallback.
   // The callback is only valid during the lifetime of the
   // ProcessSingletonStartupLock instance.
   ProcessSingleton::NotificationCallback AsNotificationCallback();

   // Executes previously queued command-line invocations and allows future
   // invocations to be executed immediately.
   void Unlock();

   bool locked() { return locked_; }

  private:

   typedef std::pair < base::CommandLine::StringVector, base::FilePath >
    DelayedStartupMessage;

   bool NotificationCallbackImpl(const base::CommandLine& command_line,
    const base::FilePath& current_directory);

   bool locked_;

   std::vector<DelayedStartupMessage> saved_startup_messages_;

   ProcessSingleton::NotificationCallback original_callback_;

   DISALLOW_COPY_AND_ASSIGN(ProcessSingletonStartupLock);
  };


  ProcessSingleton(const base::FilePath& user_data_dir,
                   const NotificationCallback& notification_callback);
  ~ProcessSingleton();

  // Notify another process, if available. Otherwise sets ourselves as the
  // singleton instance. Returns PROCESS_NONE if we became the singleton
  // instance. Callers are guaranteed to either have notified an existing
  // process or have grabbed the singleton (unless the profile is locked by an
  // unreachable process).
  // TODO(brettw): Make the implementation of this method non-platform-specific
  // by making Linux re-use the Windows implementation.
  NotifyResult NotifyOtherProcessOrCreate();

  // Sets ourself up as the singleton instance.  Returns true on success.  If
  // false is returned, we are not the singleton instance and the caller must
  // exit.
  // NOTE: Most callers should generally prefer NotifyOtherProcessOrCreate() to
  // this method, only callers for whom failure is preferred to notifying
  // another process should call this directly.
  bool Create();

  // Clear any lock state during shutdown.
  void Cleanup();

  void Unlock();

#if defined(OS_POSIX) && !defined(OS_ANDROID)
  static void DisablePromptForTesting();
#endif

 protected:
  // Notify another process, if available.
  // Returns true if another process was found and notified, false if we should
  // continue with the current process.
  // On Windows, Create() has to be called before this.
  NotifyResult NotifyOtherProcess();

#if defined(OS_POSIX) && !defined(OS_ANDROID)
  // Exposed for testing.  We use a timeout on Linux, and in tests we want
  // this timeout to be short.
  NotifyResult NotifyOtherProcessWithTimeout(
      const base::CommandLine& command_line,
      int retry_attempts,
      const base::TimeDelta& timeout,
      bool kill_unresponsive);
  NotifyResult NotifyOtherProcessWithTimeoutOrCreate(
      const base::CommandLine& command_line,
      int retry_attempts,
      const base::TimeDelta& timeout);
  void OverrideCurrentPidForTesting(base::ProcessId pid);
  void OverrideKillCallbackForTesting(
      const base::Callback<void(int)>& callback);
#endif

 private:
  NotificationCallback notification_callback_;  // Handler for notifications.

#if defined(OS_WIN)
  bool EscapeVirtualization(const base::FilePath& user_data_dir);

  HWND remote_window_;  // The HWND_MESSAGE of another browser.
  base::win::MessageWindow window_;  // The message-only window.
  bool is_virtualized_;  // Stuck inside Microsoft Softricity VM environment.
  HANDLE lock_file_;
  base::FilePath user_data_dir_;
#elif defined(OS_POSIX) && !defined(OS_ANDROID)
  // Return true if the given pid is one of our child processes.
  // Assumes that the current pid is the root of all pids of the current
  // instance.
  bool IsSameChromeInstance(pid_t pid);

  // Extract the process's pid from a symbol link path and if it is on
  // the same host, kill the process, unlink the lock file and return true.
  // If the process is part of the same chrome instance, unlink the lock file
  // and return true without killing it.
  // If the process is on a different host, return false.
  bool KillProcessByLockPath();

  // Default function to kill a process, overridable by tests.
  void KillProcess(int pid);

  // Allow overriding for tests.
  base::ProcessId current_pid_;

  // Function to call when the other process is hung and needs to be killed.
  // Allows overriding for tests.
  base::Callback<void(int)> kill_callback_;

  // Path in file system to the socket.
  base::FilePath socket_path_;

  // Path in file system to the lock.
  base::FilePath lock_path_;

  // Path in file system to the cookie file.
  base::FilePath cookie_path_;

  // Temporary directory to hold the socket.
  base::ScopedTempDir socket_dir_;

  // Helper class for linux specific messages.  LinuxWatcher is ref counted
  // because it posts messages between threads.
  class LinuxWatcher;
  scoped_refptr<LinuxWatcher> watcher_;
#endif
  ProcessSingletonStartupLock startup_lock_;

  DISALLOW_COPY_AND_ASSIGN(ProcessSingleton);
};

} // namespace dingler

#endif  // CHROME_BROWSER_PROCESS_SINGLETON_H_
