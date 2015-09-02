// Copyright 2013 The Chromium Authors. All rights reserved.
// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "kernel/kernel_child_process_host.h"

#include "base/base_switches.h"
#include "base/bind.h"
#include "base/command_line.h"
#include "base/files/file_path.h"
#include "base/lazy_instance.h"
#include "base/logging.h"
#include "base/metrics/histogram.h"
#include "base/stl_util.h"
#include "base/strings/string_util.h"
#include "base/synchronization/waitable_event.h"
#include "common/child_process_host.h"
#include "common/process_launcher_delegate.h"
#include "kernel/kernel_child_process_host_delegate.h"
#include "kernel/kernel_child_process_observer.h"
#include "kernel/kernel_thread.h"
#include "kernel/kernel_message_filter.h"
#include "kernel/child_process_data.h"
#include "common/process_type.h"
#include "common/result_code.h"

namespace kernel {
namespace {

static base::LazyInstance<KernelChildProcessHost::KernelChildProcessList>
    g_child_process_list = LAZY_INSTANCE_INITIALIZER;

base::LazyInstance<base::ObserverList<KernelChildProcessObserver> >
    g_observers = LAZY_INSTANCE_INITIALIZER;

void NotifyProcessHostConnected(const ChildProcessData& data) {
  FOR_EACH_OBSERVER(KernelChildProcessObserver, g_observers.Get(),
                    KernelChildProcessHostConnected(data));
}

void NotifyProcessHostDisconnected(const ChildProcessData& data) {
  FOR_EACH_OBSERVER(KernelChildProcessObserver, g_observers.Get(),
                    KernelChildProcessHostDisconnected(data));
}

void NotifyProcessCrashed(const ChildProcessData& data) {
  FOR_EACH_OBSERVER(KernelChildProcessObserver, g_observers.Get(),
                    KernelChildProcessCrashed(data));
}

}  // namespace

KernelChildProcessHost* KernelChildProcessHost::Create(
    int process_type,
    KernelChildProcessHostDelegate* delegate) {
  return new KernelChildProcessHost(process_type, delegate);
}

// static
KernelChildProcessHost::KernelChildProcessList*
    KernelChildProcessHost::GetIterator() {
  return g_child_process_list.Pointer();
}

// static
void KernelChildProcessHost::AddObserver(
    KernelChildProcessObserver* observer) {
 DCHECK(KernelThread::CurrentlyOn(KernelThread::MAIN));
 g_observers.Get().AddObserver(observer);
}

// static
void KernelChildProcessHost::RemoveObserver(
    KernelChildProcessObserver* observer) {
  // TODO(phajdan.jr): Check thread after fixing http://crbug.com/167126.
  g_observers.Get().RemoveObserver(observer);
}

// static 
void KernelChildProcessHost::TerminateAll() {
 DCHECK(KernelThread::CurrentlyOn(KernelThread::IO));
 // Make a copy since the KernelChildProcessHost dtor mutates the original
 // list.
 KernelChildProcessList copy = g_child_process_list.Get();
 for (KernelChildProcessList::iterator it = copy.begin();
      it != copy.end(); ++it) {
   delete (*it)->delegate();  // ~*HostDelegate deletes *HostImpl.
 }
}

KernelChildProcessHost::KernelChildProcessHost(int process_type,
    KernelChildProcessHostDelegate* delegate): data_(process_type),
      delegate_(delegate) {
 
 data_.id = common::ChildProcessHost::GenerateChildProcessUniqueId();

 child_process_host_.reset(common::ChildProcessHost::Create(this));
 //AddFilter(new TraceMessageFilter);
 //AddFilter(new ProfilerMessageFilter(process_type));
 //AddFilter(new HistogramMessageFilter);

 g_child_process_list.Get().push_back(this);
}

KernelChildProcessHost::~KernelChildProcessHost() {
 g_child_process_list.Get().remove(this);
}

bool KernelChildProcessHost::Send(IPC::Message* message) {
 return child_process_host_->Send(message);
}

void KernelChildProcessHost::Launch(base::CommandLine* cmd_line, 
  ProcessLauncherDelegate* delegate) {
 DCHECK(KernelThread::CurrentlyOn(KernelThread::IO));

 // const base::CommandLine& browser_command_line =
 //     *base::CommandLine::ForCurrentProcess();
 // static const char* kForwardSwitches[] = {
 //   switches::kDisableLogging,
 //   switches::kEnableLogging,
 //   switches::kIPCConnectionTimeout,
 //   switches::kLoggingLevel,
 //   switches::kTraceToConsole,
 //   switches::kV,
 //   switches::kVModule,
 // };
 // cmd_line->CopySwitchesFrom(browser_command_line, kForwardSwitches,
 //                            arraysize(kForwardSwitches));

 child_process_.reset(new ChildProcessLauncher(
 	   delegate,
     cmd_line,
     data_.id,
     this));
}

const ChildProcessData& KernelChildProcessHost::GetData() const {
 DCHECK(KernelThread::CurrentlyOn(KernelThread::IO));
 return data_;
}

common::ChildProcessHost* KernelChildProcessHost::GetHost() const {
 DCHECK(KernelThread::CurrentlyOn(KernelThread::IO));
 return child_process_host_.get();
}

base::TerminationStatus KernelChildProcessHost::GetTerminationStatus(
	bool known_dead,
	int* exit_code) {
 DCHECK(KernelThread::CurrentlyOn(KernelThread::IO));

 if (!child_process_)  // If the delegate doesn't use Launch() helper.
   return base::GetTerminationStatus(data_.handle, exit_code);
 return child_process_->GetChildTerminationStatus(known_dead,
                                                  exit_code);
}

void KernelChildProcessHost::SetName(const base::string16& name) {
 DCHECK(KernelThread::CurrentlyOn(KernelThread::IO));
 data_.name = name;
}

void KernelChildProcessHost::SetHandle(base::ProcessHandle handle) {
 DCHECK(KernelThread::CurrentlyOn(KernelThread::IO));
 data_.handle = handle;
}

 // KernelChildProcessHostDelegate implementation:
bool KernelChildProcessHost::CanShutdown() {
 return delegate_->CanShutdown();
}

void KernelChildProcessHost::OnChildDisconnected() {
 DCHECK(KernelThread::CurrentlyOn(KernelThread::IO));
 #if defined(os_win)
  // onchilddisconnected may be called without onchannelconnected, so stop the
  // early exit watcher so getterminationstatus can close the process handle.
  early_exit_watcher_.stopwatching();
 #endif
  if (child_process_.get() || data_.handle) {
    int exit_code;
    base::TerminationStatus status = GetTerminationStatus(
        true /* known_dead */, &exit_code);
    switch (status) {
      case base::TERMINATION_STATUS_PROCESS_CRASHED:
      case base::TERMINATION_STATUS_ABNORMAL_TERMINATION: {
        delegate_->OnProcessCrashed(exit_code);
        KernelThread::PostTask(KernelThread::MAIN, FROM_HERE,
                               base::Bind(&NotifyProcessCrashed, data_));
        UMA_HISTOGRAM_ENUMERATION("ChildProcess.Crashed2",
                                  data_.process_type,
                                  common::PROCESS_TYPE_MAX);
        break;
      }
      case base::TERMINATION_STATUS_PROCESS_WAS_KILLED: {
        delegate_->OnProcessCrashed(exit_code);
        // Report that this child process was killed.
        UMA_HISTOGRAM_ENUMERATION("ChildProcess.Killed2",
                                  data_.process_type,
                                  common::PROCESS_TYPE_MAX);
        break;
      }
      case base::TERMINATION_STATUS_STILL_RUNNING: {
        UMA_HISTOGRAM_ENUMERATION("ChildProcess.DisconnectedAlive2",
                                  data_.process_type,
                                  common::PROCESS_TYPE_MAX);
      }
      default:
        break;
    }
    UMA_HISTOGRAM_ENUMERATION("ChildProcess.Disconnected2",
                              data_.process_type,
                              common::PROCESS_TYPE_MAX);
  }
  KernelThread::PostTask(KernelThread::MAIN, FROM_HERE,
                         base::Bind(&NotifyProcessHostDisconnected, data_));
 delete delegate_;  // Will delete us
}

const base::Process& KernelChildProcessHost::GetProcess() const {
 DCHECK(KernelThread::CurrentlyOn(KernelThread::IO));
 DCHECK(child_process_.get())
     << "Requesting a child process handle before launching.";
 DCHECK(child_process_->GetProcess().IsValid())
     << "Requesting a child process handle before launch has completed OK.";
 return child_process_->GetProcess();
}

bool KernelChildProcessHost::OnMessageReceived(const IPC::Message& message){
 return delegate_->OnMessageReceived(message);
}

void KernelChildProcessHost::OnChannelConnected(int32 peer_pid) {
 #if defined(OS_WIN)
  // From this point onward, the exit of the child process is detected by an
  // error on the IPC channel.
  early_exit_watcher_.StopWatching();
 #endif

 DCHECK(KernelThread::CurrentlyOn(KernelThread::IO));
 KernelThread::PostTask(KernelThread::MAIN, FROM_HERE,
                        base::Bind(&NotifyProcessHostConnected, data_));

 delegate_->OnChannelConnected(peer_pid);
}

void KernelChildProcessHost::OnChannelError() {
 delegate_->OnChannelError();
}

void KernelChildProcessHost::OnBadMessageReceived(const IPC::Message& message) {
 child_process_->GetProcess().Terminate(common::RESULT_CODE_KILLED_BAD_MESSAGE, false);
}

// Removes this host from the host list. Calls ChildProcessHost::ForceShutdown
void KernelChildProcessHost::ForceShutdown() {
 DCHECK(KernelThread::CurrentlyOn(KernelThread::IO));
 g_child_process_list.Get().remove(this);
 child_process_host_->ForceShutdown();
}

// Callers can reduce the KernelChildProcess' priority.
void KernelChildProcessHost::SetBackgrounded(bool backgrounded) {
 child_process_->SetProcessBackgrounded(backgrounded);
}

// Controls whether the child process should be terminated on browser
// shutdown. Default is to always terminate.
void KernelChildProcessHost::SetTerminateChildOnShutdown(bool terminate_on_shutdown) {
 DCHECK(KernelThread::CurrentlyOn(KernelThread::IO));
 child_process_->SetTerminateChildOnShutdown(terminate_on_shutdown);
}

// Adds an IPC message filter.
void KernelChildProcessHost::AddFilter(KernelMessageFilter* filter) {
 child_process_host_->AddFilter(filter->GetFilter());
}

// Called when an instance of a particular child is created in a page.
// static 
void KernelChildProcessHost::NotifyProcessInstanceCreated(const ChildProcessData& data) {
 DCHECK(KernelThread::CurrentlyOn(KernelThread::MAIN));
 FOR_EACH_OBSERVER(KernelChildProcessObserver, g_observers.Get(),
                   KernelChildProcessInstanceCreated(data));
}

void KernelChildProcessHost::OnProcessLaunchFailed() {
  delegate_->OnProcessLaunchFailed();
  delete delegate_;  // Will delete us
}

void KernelChildProcessHost::OnProcessLaunched() {
  const base::Process& process = child_process_->GetProcess();
  DCHECK(process.IsValid());

#if defined(OS_WIN)
  // Start a WaitableEventWatcher that will invoke OnProcessExitedEarly if the
  // child process exits. This watcher is stopped once the IPC channel is
  // connected and the exit of the child process is detecter by an error on the
  // IPC channel thereafter.
  DCHECK(!early_exit_watcher_.GetWatchedObject());
  early_exit_watcher_.StartWatching(process.Handle(), this);
#endif

  // TODO(rvargas) crbug.com/417532: Don't store a handle.
  data_.handle = process.Handle();
  delegate_->OnProcessLaunched();
}

#if defined(OS_WIN)
void KernelChildProcessHost::OnObjectSignaled(HANDLE object) {
 OnChildDisconnected();
}
#endif

}