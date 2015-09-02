// Copyright 2013 The Chromium Authors. All rights reserved.
// Copyright (c) 2015 Stripes. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KERNEL_KERNEL_CHILD_PROCESS_HOST_H_
#define KERNEL_KERNEL_CHILD_PROCESS_HOST_H_

#include <list>

#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/process/process.h"
#include "base/synchronization/waitable_event_watcher.h"
#include "ipc/ipc_sender.h"
#include "kernel/child_process_launcher.h"
#include "kernel/child_process_data.h"
#include "common/child_process_host_delegate.h"
#if defined(OS_WIN)
#include "base/win/object_watcher.h"
#endif

namespace common{
class ChildProcessHost;
}

namespace kernel {
class KernelChildProcessHostDelegate;
class KernelChildProcessObserver;
class KernelChildProcessHostIterator;
class KernelMessageFilter;
class ProcessLauncherDelegate;

class KernelChildProcessHost : public IPC::Sender,
        public common::ChildProcessHostDelegate,
#if defined(OS_WIN)
          public base::win::ObjectWatcher::Delegate,
#endif
          public ChildProcessLauncher::Client {
public:
 typedef std::list<KernelChildProcessHost*> KernelChildProcessList;

 static KernelChildProcessHost* Create(
    int process_type,
    KernelChildProcessHostDelegate* delegate);

 explicit KernelChildProcessHost(int process_type,
  KernelChildProcessHostDelegate* delegate);
 ~KernelChildProcessHost() override;

 static void TerminateAll();

 bool Send(IPC::Message* message) override;
 void Launch(base::CommandLine* cmd_line, 
 	ProcessLauncherDelegate* delegate);
 const ChildProcessData& GetData() const;
 common::ChildProcessHost* GetHost() const;
 base::TerminationStatus GetTerminationStatus(bool known_dead,
                                              int* exit_code);
 void SetName(const base::string16& name);
 void SetHandle(base::ProcessHandle handle);

 // ShellChildProcessHostDelegate implementation:
 bool CanShutdown() override;
 void OnChildDisconnected() override;
 const base::Process& GetProcess() const override;
 bool OnMessageReceived(const IPC::Message& message) override;
 void OnChannelConnected(int32 peer_pid) override;
 void OnChannelError() override;
 void OnBadMessageReceived(const IPC::Message& message) override;

 // Removes this host from the host list. Calls ChildProcessHost::ForceShutdown
 void ForceShutdown();

 // Callers can reduce the ShellChildProcess' priority.
 void SetBackgrounded(bool backgrounded);

 // Controls whether the child process should be terminated on browser
 // shutdown. Default is to always terminate.
 void SetTerminateChildOnShutdown(bool terminate_on_shutdown);

 // Adds an IPC message filter.
 void AddFilter(KernelMessageFilter* filter);

 // Called when an instance of a particular child is created in a page.
 static void NotifyProcessInstanceCreated(const ChildProcessData& data);

 KernelChildProcessHostDelegate* delegate() const { return delegate_; }

private:
 friend class KernelChildProcessObserver;
 friend class KernelChildProcessHostIterator;
 static KernelChildProcessList* GetIterator();

 static void AddObserver(KernelChildProcessObserver* observer);
 static void RemoveObserver(KernelChildProcessObserver* observer);

 // ChildProcessLauncher::Client implementation.
 void OnProcessLaunched() override;
 void OnProcessLaunchFailed() override;

#if defined(OS_WIN)
 // ObjectWatcher::Delegate implementation.
 void OnObjectSignaled(HANDLE object) override;
#endif

 ChildProcessData data_;
 KernelChildProcessHostDelegate* delegate_;
 scoped_ptr<common::ChildProcessHost> child_process_host_;
 scoped_ptr<ChildProcessLauncher> child_process_;

#if defined(OS_WIN)
 // Watches to see if the child process exits before the IPC channel has
 // been connected. Thereafter, its exit is determined by an error on the
 // IPC channel.
 base::win::ObjectWatcher early_exit_watcher_;
#endif

 
 DISALLOW_COPY_AND_ASSIGN(KernelChildProcessHost);
};

}

#endif // KERNEL_KERNEL_CHILD_PROCESS_HOST_H_
