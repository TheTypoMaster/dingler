// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KERNEL_MAIN_LOOP_H__
#define KERNEL_MAIN_LOOP_H__

#include "base/basictypes.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/timer/timer.h"
#include "common/main_params.h"
#include "kernel/process_singleton.h"

namespace base {
class CommandLine;
class MessageLoop;
class PowerMonitor;
}  // namespace base

namespace kernel {
class KernelProcess;
class KernelThread;
class KernelProcessSubThread;
class StartupTaskRunner;

class KernelMainLoop {
public:

 static KernelMainLoop* GetInstance();

 KernelMainLoop(const common::MainParams& parameters);
 ~KernelMainLoop();

 int result_code() const { return result_code_; }

 const base::CommandLine& parsed_command_line() const { return parsed_command_line_; }

 void Init();
 void EarlyInitialization();
 void MainMessageLoopStart();
 void CreateStartupTasks();
 void RunMainMessageLoop();
 void ShutdownThreadsAndCleanUp();

private:
 
 void InitializeMainThread();
 int PreCreateThreads();
 int CreateThreads();
 int KernelThreadsStarted();
 int PreMainMessageLoopRun();

 const common::MainParams& parameters_;
 const base::CommandLine& parsed_command_line_;
 int result_code_;

 bool created_threads_;

 scoped_ptr<base::MessageLoop> main_message_loop_;

 scoped_ptr<StartupTaskRunner> startup_task_runner_;

 scoped_ptr<ProcessSingleton> process_singleton_;

 scoped_ptr<KernelProcess> kernel_process_;

 scoped_ptr<KernelThread> main_thread_;

 scoped_ptr<KernelProcessSubThread> io_thread_;
 scoped_ptr<KernelProcessSubThread> file_thread_;
 scoped_ptr<KernelProcessSubThread> container_thread_;
 scoped_ptr<KernelProcessSubThread> process_launcher_thread_;

 base::FilePath root_dir_;

 ProcessSingleton::NotifyResult notify_result_;

 bool should_run_;

 DISALLOW_COPY_AND_ASSIGN(KernelMainLoop);
};

}

#endif
