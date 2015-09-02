// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "kernel/child_process_launcher.h"

#include <utility>  // For std::pair.

#include "base/bind.h"
#include "base/command_line.h"
#include "base/files/file_util.h"
#include "base/files/scoped_file.h"
#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "base/metrics/histogram.h"
#include "base/process/process.h"
#include "base/synchronization/lock.h"
#include "base/threading/thread.h"
#include "base/memory/shared_memory.h"
#include "base/memory/singleton.h"
#if defined(OS_POSIX)
#include "base/metrics/stats_table.h"
#include "base/posix/global_descriptors.h"
#endif
#include "common/result_code.h"
#include "common/switches.h"
#include "common/process_launcher_delegate.h"
#include "common/file_descriptor_info_impl.h"
#include "kernel/kernel_thread.h"

namespace kernel {

// Having the functionality of ChildProcessLauncher be in an internal
// ref counted object allows us to automatically terminate the process when the
// parent class destructs, while still holding on to state that we need.
class ChildProcessLauncher::Context
    : public base::RefCountedThreadSafe<ChildProcessLauncher::Context> {
 public:
  Context();

  // Posts a task to a dedicated thread to do the actual work.
  // Must be called on the UI thread.
  void Launch(ProcessLauncherDelegate* delegate,
              base::CommandLine* cmd_line,
              int child_process_id,
              Client* client);

  // Resets the client (the client is going away).
  void ResetClient();

  bool starting() const { return starting_; }

  const base::Process& process() const { return process_; }

  int exit_code() const { return exit_code_; }

  base::TerminationStatus termination_status() const {
    return termination_status_;
  }

  void set_terminate_child_on_shutdown(bool terminate_on_shutdown) {
    terminate_child_on_shutdown_ = terminate_on_shutdown;
  }

  void UpdateTerminationStatus(bool known_dead);

  void Close() { process_.Close(); }

  void SetProcessBackgrounded(bool background);

 private:
  friend class base::RefCountedThreadSafe<ChildProcessLauncher::Context>;

  ~Context() {
    Terminate();
  }

  static void RecordHistograms(base::TimeTicks begin_launch_time);
  static void RecordLaunchHistograms(base::TimeDelta launch_time);

  // Performs the actual work of launching the process.
  // Runs on the PROCESS_LAUNCHER thread.
  static void LaunchInternal(
      // |this_object| is NOT thread safe. Only use it to post a task back.
      scoped_refptr<Context> this_object,
      KernelThread::ID client_thread_id,
      int child_process_id,
      ProcessLauncherDelegate* delegate,
      base::CommandLine* cmd_line);

  // Notifies the client about the result of the operation.
  // Runs on the UI thread.
  void Notify(
      base::Process process);

  void Terminate();

  static void SetProcessBackgroundedInternal(base::Process process,
                                             bool background);

  static void TerminateInternal(
   base::Process process);

  Client* client_;
  KernelThread::ID client_thread_id_;
  base::Process process_;
  base::TerminationStatus termination_status_;
  int exit_code_;
  bool starting_;
  // Controls whether the child process should be terminated on browser
  // shutdown. Default behavior is to terminate the child.
  bool terminate_child_on_shutdown_;
};

ChildProcessLauncher::Context::Context()
    : client_(NULL),
    client_thread_id_(KernelThread::MAIN),
      termination_status_(base::TERMINATION_STATUS_NORMAL_TERMINATION),
      exit_code_(common::RESULT_CODE_NORMAL_EXIT),
      starting_(true),
      // TODO(earthdok): Re-enable on CrOS http://crbug.com/360622
#if (defined(ADDRESS_SANITIZER) || defined(LEAK_SANITIZER) || \
     defined(THREAD_SANITIZER))
      terminate_child_on_shutdown_(false) {
#else
      terminate_child_on_shutdown_(true) {
#endif
}

void ChildProcessLauncher::Context::Launch(
    ProcessLauncherDelegate* delegate,
    base::CommandLine* cmd_line,
    int child_process_id,
    Client* client) {
 CHECK(KernelThread::GetCurrentThreadIdentifier(&client_thread_id_));
  client_ = client;

  KernelThread::PostTask(
   KernelThread::PROCESS_LAUNCHER, FROM_HERE,
      base::Bind(&Context::LaunchInternal,
                 make_scoped_refptr(this),
                 client_thread_id_,
                 child_process_id,
                 delegate,
                 cmd_line));
}

void ChildProcessLauncher::Context::ResetClient() {
  // No need for locking as this function gets called on the same thread that
  // client_ would be used.
 CHECK(KernelThread::CurrentlyOn(client_thread_id_));
  client_ = NULL;
}

void ChildProcessLauncher::Context::UpdateTerminationStatus(bool known_dead) {
#if defined(OS_POSIX) && !defined(OS_MACOSX) && !defined(OS_ANDROID)
 if (zygote_) {
  termination_status_ = ZygoteHostImpl::GetInstance()->
   GetTerminationStatus(process_.Handle(), known_dead, &exit_code_);
 }
 else if (known_dead) {
  termination_status_ =
   base::GetKnownDeadTerminationStatus(process_.Handle(), &exit_code_);
 }
 else {
#elif defined(OS_MACOSX)
 if (known_dead) {
  termination_status_ =
   base::GetKnownDeadTerminationStatus(process_.Handle(), &exit_code_);
 }
 else {
#elif defined(OS_ANDROID)
 if (IsChildProcessOomProtected(process_.Handle())) {
  termination_status_ = base::TERMINATION_STATUS_OOM_PROTECTED;
 }
 else {
#else
  {
#endif
   termination_status_ =
    base::GetTerminationStatus(process_.Handle(), &exit_code_);
  }
}

void ChildProcessLauncher::Context::SetProcessBackgrounded(bool background) {
  base::Process to_pass = process_.Duplicate();
  KernelThread::PostTask(
   KernelThread::PROCESS_LAUNCHER, FROM_HERE,
      base::Bind(&Context::SetProcessBackgroundedInternal,
                 base::Passed(&to_pass), background));
}

// static
void ChildProcessLauncher::Context::RecordHistograms(
    base::TimeTicks begin_launch_time) {
  base::TimeDelta launch_time = base::TimeTicks::Now() - begin_launch_time;
  if (KernelThread::CurrentlyOn(KernelThread::PROCESS_LAUNCHER)) {
    RecordLaunchHistograms(launch_time);
  } else {
   KernelThread::PostTask(
    KernelThread::PROCESS_LAUNCHER, FROM_HERE,
        base::Bind(&ChildProcessLauncher::Context::RecordLaunchHistograms,
                   launch_time));
  }
}

// static
void ChildProcessLauncher::Context::RecordLaunchHistograms(
    base::TimeDelta launch_time) {
  // Log the launch time, separating out the first one (which will likely be
  // slower due to the rest of the browser initializing at the same time).
  static bool done_first_launch = false;
  if (done_first_launch) {
    UMA_HISTOGRAM_TIMES("MPArch.ChildProcessLaunchSubsequent", launch_time);
  } else {
    UMA_HISTOGRAM_TIMES("MPArch.ChildProcessLaunchFirst", launch_time);
    done_first_launch = true;
  }
}

// static
void ChildProcessLauncher::Context::LaunchInternal(
    // |this_object| is NOT thread safe. Only use it to post a task back.
    scoped_refptr<Context> this_object,
    KernelThread::ID client_thread_id,
    int child_process_id,
    ProcessLauncherDelegate* delegate,
    base::CommandLine* cmd_line) {
//  scoped_ptr<ProcessLauncherDelegate> delegate_deleter(delegate);
//  base::EnvironmentMap env = delegate->GetEnvironment();
//  base::ScopedFD ipcfd = delegate->TakeIpcFd();
//  scoped_ptr<base::CommandLine> cmd_line_deleter(cmd_line);
//  base::TimeTicks begin_launch_time = base::TimeTicks::Now();
//
//  std::string process_type =
//      cmd_line->GetSwitchValueASCII(switches::kProcessType);
//  scoped_ptr<FileDescriptorInfo> files_to_register(
//      FileDescriptorInfoImpl::Create());
//
//  files_to_register->Transfer(kPrimaryIPCChannel, ipcfd.Pass());
//  base::StatsTable* stats_table = base::StatsTable::current();
//  if (stats_table &&
//      base::SharedMemory::IsHandleValid(stats_table->GetSharedMemoryHandle())) {
//    base::FileDescriptor fd = stats_table->GetSharedMemoryHandle();
//    DCHECK(!fd.auto_close);
//    files_to_register->Share(kStatsTableSharedMemFd, fd.fd);
//  }
//
//  base::ProcessHandle handle = base::kNullProcessHandle;
  // We need to close the client end of the IPC channel to reliably detect
  // child termination.

//  GetContentClient()->browser()->GetAdditionalMappedFilesForChildProcess(
//      *cmd_line, child_process_id, files_to_register.get());
  
   // Convert FD mapping to FileHandleMappingVector
//    base::FileHandleMappingVector fds_to_map =
//        files_to_register->GetMappingWithIDAdjustment(
//            base::GlobalDescriptors::kBaseDescriptor);

//    if (process_type == switches::kRendererProcess) {
//      const int sandbox_fd =
//          RenderSandboxHostLinux::GetInstance()->GetRendererSocket();
//      fds_to_map.push_back(std::make_pair(
//          sandbox_fd,
//          GetSandboxFD()));
//    }
    // Actually launch the app.
//    base::LaunchOptions options;
//    options.environ = env;
//    options.fds_to_remap = &fds_to_map;
//
//    bool launched = base::LaunchProcess(*cmd_line, options, &handle);
//    if (!launched)
//      handle = base::kNullProcessHandle;
//  
//  base::Process process(handle);
//  if (process.IsValid())
//    RecordHistograms(begin_launch_time);
//  ShellThread::PostTask(
//      client_thread_id, FROM_HERE,
//      base::Bind(&Context::Notify,
//                 this_object.get(),
//                 base::Passed(&process)));
}

void ChildProcessLauncher::Context::Notify(
    base::Process process) {
  starting_ = false;
  process_ = process.Pass();
  if (!process_.IsValid())
    LOG(ERROR) << "Failed to launch child process";

  if (client_) {
    if (process_.IsValid()) {
      client_->OnProcessLaunched();
    } else {
      client_->OnProcessLaunchFailed();
    }
  } else {
    Terminate();
  }
}

void ChildProcessLauncher::Context::Terminate() {
  if (!process_.IsValid())
    return;

  if (!terminate_child_on_shutdown_)
    return;

  // On Posix, EnsureProcessTerminated can lead to 2 seconds of sleep!  So
  // don't this on the UI/IO threads.
  KernelThread::PostTask(
   KernelThread::PROCESS_LAUNCHER, FROM_HERE,
      base::Bind(&Context::TerminateInternal,
                base::Passed(&process_)));
}

// static
void ChildProcessLauncher::Context::SetProcessBackgroundedInternal(
    base::Process process,
    bool background) {
  process.SetProcessBackgrounded(background);
}

// static
void ChildProcessLauncher::Context::TerminateInternal(
  base::Process process) {
  // Client has gone away, so just kill the process.  Using exit code 0
  // means that UMA won't treat this as a crash.
 process.Terminate(common::RESULT_CODE_NORMAL_EXIT, false);
  // On POSIX, we must additionally reap the child.
}

// -----------------------------------------------------------------------------

ChildProcessLauncher::ChildProcessLauncher(
    ProcessLauncherDelegate* delegate,
    base::CommandLine* cmd_line,
    int child_process_id,
    Client* client) {
  context_ = new Context();
  context_->Launch(
      delegate,
      cmd_line,
      child_process_id,
      client);
}

ChildProcessLauncher::~ChildProcessLauncher() {
  context_->ResetClient();
}

bool ChildProcessLauncher::IsStarting() {
  return context_->starting();
}

const base::Process& ChildProcessLauncher::GetProcess() const {
  DCHECK(!context_->starting());
  return context_->process();
}

base::TerminationStatus ChildProcessLauncher::GetChildTerminationStatus(
    bool known_dead,
    int* exit_code) {
  if (!context_->process().IsValid()) {
    // Process is already gone, so return the cached termination status.
    if (exit_code)
      *exit_code = context_->exit_code();
    return context_->termination_status();
  }

  context_->UpdateTerminationStatus(known_dead);
  if (exit_code)
    *exit_code = context_->exit_code();

  // POSIX: If the process crashed, then the kernel closed the socket
  // for it and so the child has already died by the time we get
  // here. Since GetTerminationStatus called waitpid with WNOHANG,
  // it'll reap the process.  However, if GetTerminationStatus didn't
  // reap the child (because it was still running), we'll need to
  // Terminate via ProcessWatcher. So we can't close the handle here.
  if (context_->termination_status() != base::TERMINATION_STATUS_STILL_RUNNING)
    context_->Close();

  return context_->termination_status();
}

void ChildProcessLauncher::SetProcessBackgrounded(bool background) {
  context_->SetProcessBackgrounded(background);
}

void ChildProcessLauncher::SetTerminateChildOnShutdown(
    bool terminate_on_shutdown) {
  if (context_.get())
    context_->set_terminate_child_on_shutdown(terminate_on_shutdown);
}


}