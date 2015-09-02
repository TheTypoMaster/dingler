// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KERNEL_PROCESS_H__
#define KERNEL_PROCESS_H__

#include "base/basictypes.h"
#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/ref_counted.h"
#include "base/supports_user_data.h"
#include "base/threading/non_thread_safe.h"
#include "base/sequenced_task_runner.h"
#include "common/main_params.h"

class PrefService;

namespace kernel {
class PrefRegistrySyncable;
class ContainerManager;
class IOThread;

class KernelProcess : public base::NonThreadSafe,
                      public base::SupportsUserData {
public:
 
 static KernelProcess* current();

 KernelProcess(const base::FilePath& path, 
               base::SequencedTaskRunner* local_state_task_runner,
               const common::MainParams& main_params);

 ~KernelProcess() override;

 ContainerManager* container_manager() const;
 IOThread* io_thread() const;

 // Called before the browser threads are created.
 void PreCreateThreads();

 // Called after the threads have been created but before the message loops
 // starts running. Allows the browser process to do any initialization that
 // requires all threads running.
 void PreMainMessageLoopRun();

 // Most cleanup is done by these functions, driven from
 // DinglerShellMain based on notifications from the content
 // framework, rather than in the destructor, so that we can
 // interleave cleanup with threads being stopped.
 void StartTearDown();
 void PostMainMessageLoopRun();
 void PostDestroyThreads();

 void Shutdown();

 unsigned int AddRefModule();
 unsigned int ReleaseModule();

 bool IsShuttingDown();

private:
 
 unsigned int module_ref_count_;
 bool did_start_;

 const common::MainParams& main_params_;

 // Sequenced task runner for local state related I/O tasks.
 const scoped_refptr<base::SequencedTaskRunner> local_state_task_runner_;

 scoped_ptr<ContainerManager> container_manager_;

 scoped_ptr<IOThread> io_thread_;

 scoped_refptr<PrefRegistrySyncable> pref_registry_;

 scoped_ptr<PrefService> prefs_;

 base::FilePath path_;

 DISALLOW_COPY_AND_ASSIGN(KernelProcess);
};

extern KernelProcess* g_kernel_process;

}

#endif
