// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "kernel/kernel_main_loop.h"

#include "base/path_service.h"
#include "base/command_line.h"
#include "base/logging.h"
#include "base/message_loop/message_loop.h"
#include "base/pending_task.h"
#include "base/path_service.h"
#include "base/run_loop.h"
#include "base/thread_task_runner_handle.h"
#include "base/threading/thread_restrictions.h"
#include "base/i18n/icu_util.h"
#include "base/prefs/json_pref_store.h"
#include "common/paths.h"
#include "common/result_code.h"
#include "common/constants.h"
#include "kernel/notification_service.h"
#include "kernel/kernel_process_subthread.h"
#include "kernel/kernel_thread.h"
#include "kernel/kernel_process.h"
#include "kernel/kernel_startup.h"
#include "kernel/startup_task_runner.h"
#include "kernel/io_thread.h"

#if defined(OS_WIN)
#include <windows.h>
#include <commctrl.h>
#include <shellapi.h>
#include "net/base/winsock_init.h"
#endif

namespace kernel {

namespace {

 NOINLINE void ResetThread_FILE(scoped_ptr<KernelProcessSubThread> thread) {
  volatile int inhibit_comdat = __LINE__;
  ALLOW_UNUSED_LOCAL(inhibit_comdat);
  thread.reset();
 }

 NOINLINE void ResetThread_PROCESS_LAUNCHER(
  scoped_ptr<KernelProcessSubThread> thread) {
  volatile int inhibit_comdat = __LINE__;
  ALLOW_UNUSED_LOCAL(inhibit_comdat);
  thread.reset();
 }

 NOINLINE void ResetThread_IO(scoped_ptr<KernelProcessSubThread> thread) {
  volatile int inhibit_comdat = __LINE__;
  ALLOW_UNUSED_LOCAL(inhibit_comdat);
  thread.reset();
 }

 NOINLINE void ResetThread_CONTAINER(scoped_ptr<KernelProcessSubThread> thread) {
  volatile int inhibit_comdat = __LINE__;
  ALLOW_UNUSED_LOCAL(inhibit_comdat);
  thread.reset();
 }

 base::FilePath GetStartupRootPath() {
  base::FilePath root_dir;
  PathService::Get(common::DIR_ROOT, &root_dir);
  return root_dir;
 }

 bool ProcessSingletonNotificationCallback(
  const base::CommandLine& command_line,
  const base::FilePath& current_directory) {
  // Drop the request if the browser process is already in shutdown path.
  if (!KernelProcess::current())
   return false;

  base::FilePath startup_root_dir =
   GetStartupRootPath();

  KernelStartup::ProcessCommandLineAlreadyRunning(
   command_line, current_directory, startup_root_dir);

  return true;
 }

} // namespace


KernelMainLoop* g_current_kernel_main_loop = NULL;

// static 
KernelMainLoop* KernelMainLoop::GetInstance() {
 DCHECK(KernelThread::CurrentlyOn(KernelThread::MAIN));
 return g_current_kernel_main_loop;
}

KernelMainLoop::KernelMainLoop(const common::MainParams& parameters) : parameters_(parameters),
  parsed_command_line_(parameters.command_line),
  result_code_(common::RESULT_CODE_NORMAL_EXIT),
  created_threads_(false),
  notify_result_(ProcessSingleton::PROCESS_NONE),
  should_run_(true) {
 DCHECK(!g_current_kernel_main_loop);
 g_current_kernel_main_loop = this;
}

KernelMainLoop::~KernelMainLoop() {
 DCHECK_EQ(this, g_current_kernel_main_loop);

 g_current_kernel_main_loop = NULL;
}

void KernelMainLoop::Init() {

 common::RegisterPathProvider();

 base::i18n::InitializeICU();

 root_dir_ = std::move(GetStartupRootPath());
}

void KernelMainLoop::EarlyInitialization() {
#if defined(OS_WIN)
 net::EnsureWinsockInit();
#endif
//#if !defined(USE_OPENSSL)
// // We want to be sure to init NSPR on the main thread.
// crypto::EnsureNSPRInit();
//#endif  // !defined(USE_OPENSSL)
}

void KernelMainLoop::MainMessageLoopStart() {
 if (!base::MessageLoop::current())
  main_message_loop_.reset(new base::MessageLoopForUI); // maybe forIO ?

 InitializeMainThread();

 scoped_refptr<base::SequencedTaskRunner> local_state_task_runner =
  JsonPrefStore::GetTaskRunnerForFile(
  base::FilePath(constants::kLocalStorePoolName),
  KernelThread::GetBlockingPool());

 kernel_process_.reset(new KernelProcess(root_dir_, local_state_task_runner.get(), parameters_));

}

void KernelMainLoop::CreateStartupTasks() {
 if (!startup_task_runner_.get()) {

  startup_task_runner_ = make_scoped_ptr(new StartupTaskRunner(
   base::Callback<void(int)>(),
   base::ThreadTaskRunnerHandle::Get()));

  StartupTask pre_create_threads =
   base::Bind(&KernelMainLoop::PreCreateThreads, base::Unretained(this));
  startup_task_runner_->AddTask(pre_create_threads);

  StartupTask create_threads =
   base::Bind(&KernelMainLoop::CreateThreads, base::Unretained(this));
  startup_task_runner_->AddTask(create_threads);

  StartupTask shell_thread_started = base::Bind(
   &KernelMainLoop::KernelThreadsStarted, base::Unretained(this));
  startup_task_runner_->AddTask(shell_thread_started);

  StartupTask pre_main_message_loop_run = base::Bind(
   &KernelMainLoop::PreMainMessageLoopRun, base::Unretained(this));
  startup_task_runner_->AddTask(pre_main_message_loop_run);
 }

 startup_task_runner_->RunAllTasksNow();
}

void KernelMainLoop::RunMainMessageLoop() {
 DCHECK(base::MessageLoopForUI::IsCurrent());

 if (should_run_) {
  if (parameters_.ui_task)
   base::MessageLoopForUI::current()->PostTask(FROM_HERE,
   *parameters_.ui_task);
  //base::RunLoop run_loop;
  //run_loop.Run();
  base::MessageLoopForUI::current()->Run();
 }
}

void KernelMainLoop::ShutdownThreadsAndCleanUp() {
 if (!created_threads_)
  return;


 if (notify_result_ == ProcessSingleton::PROCESS_NONE)
  process_singleton_->Cleanup();

 kernel_process_->StartTearDown();

 // Teardown may start in PostMainMessageLoopRun, and during teardown we
 // need to be able to perform IO.
 base::ThreadRestrictions::SetIOAllowed(true);
 KernelThread::PostTask(
  KernelThread::IO, FROM_HERE,
  base::Bind(base::IgnoreResult(&base::ThreadRestrictions::SetIOAllowed),
  true));


 kernel_process_->PostMainMessageLoopRun();

 for (size_t thread_id = KernelThread::MAX - 1;
  thread_id >= (KernelThread::MAIN + 1);
  --thread_id) {
  // Find the thread object we want to stop. Looping over all valid
  // KernelThread IDs and DCHECKing on a missing case in the switch
  // statement helps avoid a mismatch between this code and the
  // KernelThread::ID enumeration.
  //
  // The destruction order is the reverse order of occurrence in the
  // KernelThread::ID list. The rationale for the order is as
  // follows (need to be filled in a bit):
  //
  //
  // - The IO thread is the only user of the CACHE thread.
  //
  // - The PROCESS_LAUNCHER thread must be stopped after IO in case
  //   the IO thread posted a task to terminate a process on the
  //   process launcher thread.
  //
  // - (Not sure why DB stops last.)
  switch (thread_id) {
  case KernelThread::FILE: {
   ResetThread_FILE(file_thread_.Pass());
   break;
  }
  case KernelThread::PROCESS_LAUNCHER: {
   ResetThread_PROCESS_LAUNCHER(process_launcher_thread_.Pass());
   break;
  }
  case KernelThread::IO: {
   ResetThread_IO(io_thread_.Pass());
   break;
  }
  case KernelThread::CONTAINER: {
   ResetThread_CONTAINER(container_thread_.Pass());
   break;
  }
  case KernelThread::MAIN:
  case KernelThread::MAX:
  default:
   NOTREACHED();
   break;
  }
 }

 KernelThread::ShutdownThreadPool();

 kernel_process_->PostDestroyThreads();
 kernel_process_.release();

 delete g_kernel_process;
 g_kernel_process = nullptr;

 process_singleton_.reset();
}

void KernelMainLoop::InitializeMainThread() {
 const char* kThreadName = "DinglerShellMain";
 base::PlatformThread::SetName(kThreadName);
 if (main_message_loop_)
  main_message_loop_->set_thread_name(kThreadName);

 // Register the main thread by instantiating it, but don't call any methods.
 main_thread_.reset(
  new KernelThread(KernelThread::MAIN, base::MessageLoop::current()));
}

int KernelMainLoop::PreCreateThreads() {

 process_singleton_.reset(new ProcessSingleton(
  root_dir_, base::Bind(&ProcessSingletonNotificationCallback)));

 kernel_process_->PreCreateThreads();

 return 0;
}

int KernelMainLoop::CreateThreads() {

 base::Thread::Options default_options;
 base::Thread::Options io_message_loop_options;
 io_message_loop_options.message_loop_type = base::MessageLoop::TYPE_IO;
 base::Thread::Options ui_message_loop_options;
 ui_message_loop_options.message_loop_type = base::MessageLoop::TYPE_UI;
 // Start threads in the order they occur in the KernelThread::ID
 // enumeration, except for KernelThread::MAIN which is the main
 // thread.
 //
 // Must be size_t so we can increment it.
 for (size_t thread_id = KernelThread::MAIN + 1;
  thread_id < KernelThread::MAX;
  ++thread_id) {
  scoped_ptr<KernelProcessSubThread>* thread_to_start = NULL;
  base::Thread::Options* options = &default_options;

  switch (thread_id) {
  case KernelThread::FILE:
   thread_to_start = &file_thread_;
#if defined(OS_WIN)
   // On Windows, the FILE thread needs to be have a UI message loop
   // which pumps messages in such a way that Google Update can
   // communicate back to us.
   options = &ui_message_loop_options;
#else
   options = &io_message_loop_options;
#endif
   options->timer_slack = base::TIMER_SLACK_MAXIMUM;
   break;
  case KernelThread::PROCESS_LAUNCHER:
   thread_to_start = &process_launcher_thread_;
   options->timer_slack = base::TIMER_SLACK_MAXIMUM;
   break;
  case KernelThread::IO:
   thread_to_start = &io_thread_;
   options = &io_message_loop_options;
   break;
  case KernelThread::CONTAINER:
   thread_to_start = &container_thread_;
   options->timer_slack = base::TIMER_SLACK_MAXIMUM;
   break;
  case KernelThread::MAIN:
  case KernelThread::MAX:
  default:
   NOTREACHED();
   break;
  }
  KernelThread::ID id = static_cast<KernelThread::ID>(thread_id);
  if (thread_to_start) {
   (*thread_to_start).reset(new KernelProcessSubThread(id));
   if (!(*thread_to_start)->StartWithOptions(*options)) {
    LOG(FATAL) << "Failed to start the shell thread: id == " << id;
   }
  }
  else {
   NOTREACHED();
  }
 }
 created_threads_ = true;
 return result_code_;
}

int KernelMainLoop::KernelThreadsStarted() {
 return 0;
}

int KernelMainLoop::PreMainMessageLoopRun() {

#if defined(USE_X11)
 ui::TouchFactory::SetTouchDeviceListFromCommandLine();
#endif

 kernel_process_->PreMainMessageLoopRun();

 notify_result_ = process_singleton_->NotifyOtherProcessOrCreate();
 switch (notify_result_) {
 case ProcessSingleton::PROCESS_NONE:
  // No process already running, fall through to starting a new one.
  break;

 case ProcessSingleton::PROCESS_NOTIFIED:
  should_run_ = false;
  //    printf("%s\n", base::SysWideToNativeMB(base::UTF16ToWide(
  //        l10n_util::GetStringUTF16(IDS_USED_EXISTING_BROWSER))).c_str());
  // Having a differentiated return type for testing allows for tests to
  // verify proper handling of some switches. When not testing, stick to
  // the standard Unix convention of returning zero when things went as
  // expected.
  //if (parsed_command_line().HasSwitch(switches::kTestType))
  //  return RESULT_CODE_NORMAL_EXIT_PROCESS_NOTIFIED;
  return common::RESULT_CODE_NORMAL_EXIT;

 case ProcessSingleton::PROFILE_IN_USE:
  return common::RESULT_CODE_PROFILE_IN_USE;

 case ProcessSingleton::LOCK_ERROR:
  LOG(ERROR) << "Failed to create a ProcessSingleton for your profile "
   "directory. This means that running multiple instances "
   "would start multiple browser processes rather than "
   "opening a new window in the existing process. Aborting "
   "now to avoid profile corruption.";
  return common::RESULT_CODE_PROFILE_IN_USE;

 default:
  NOTREACHED();
 }

 process_singleton_->Unlock();

 // If the MAIN thread blocks, the whole shell is unresponsive.
 // Do not allow disk IO from the MAIN thread.
 base::ThreadRestrictions::SetIOAllowed(false);
 base::ThreadRestrictions::DisallowWaiting();

 return result_code_;
}


}
