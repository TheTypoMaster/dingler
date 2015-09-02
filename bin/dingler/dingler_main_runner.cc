// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "bin/dingler/dingler_main_runner.h"

#include "base/at_exit.h"
#include "base/allocator/allocator_extension.h"
#include "base/command_line.h"
#include "base/debug/debugger.h"
#include "base/files/file_path.h"
#include "base/lazy_instance.h"
#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/path_service.h"
#include "base/process/launch.h"
#include "base/process/memory.h"
#include "base/process/process_handle.h"
#include "base/profiler/alternate_timer.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/string_util.h"
#include "base/strings/stringprintf.h"
#include "ipc/ipc_descriptors.h"
#include "ipc/ipc_switches.h"
#include "common/main_params.h"
#include "common/switches.h"
#include "common/client.h"
#include "kernel/kernel_main.h"
#include "kernel/kernel_client.h"
#include "container/host/container_main.h"
//#include "container/container_client.h"
#include "application/application_main.h"
//#include "application/application_client.h"
#include "command/command_main.h"

#if defined(USE_TCMALLOC)
#include "third_party/tcmalloc/chromium/src/gperftools/tcmalloc.h"
#include "third_party/tcmalloc/chromium/src/gperftools/malloc_extension.h"
#endif

#if defined(OS_POSIX)
#include <signal.h>

#include "base/posix/global_descriptors.h"

#endif // OS_POSIX

using base::CommandLine;

base::LazyInstance<kernel::KernelClient>
 g_kernel_client = LAZY_INSTANCE_INITIALIZER;

//base::LazyInstance<container::ContainerClient>
// g_container_client = LAZY_INSTANCE_INITIALIZER;
//
//base::LazyInstance<application::ApplicationClient>
// g_application_client = LAZY_INSTANCE_INITIALIZER;

namespace dingler {

class ClientInitializer {
public:
  static void Set(const std::string& process_type,
   MainRunner* runner) {
   common::Client* client = common::GetClient();
   if (process_type.empty()) {
    if (runner)
     client->kernel_client_ = runner->CreateKernelClient();
    //if (!content_client->browser_)
    // content_client->browser_ = &g_empty_content_browser_client.Get();
   }

   
   //if (process_type == switches::kContainerProcess) {
   // if (runner)
   //  client->container_client_ = runner->CreateContainerClient();
   // //if (!content_client->renderer_)
   // //content_client->renderer_ = &g_empty_content_renderer_client.Get();
   //}

   //if (process_type == switches::kApplicationProcess) {
   // if (runner)
   //  client->application_client_ = runner->CreateApplicationClient();
   //}
  }
 };

#if defined(OS_POSIX) && !defined(OS_IOS)

 // Setup signal-handling state: resanitize most signals, ignore SIGPIPE.
 void SetupSignalHandlers() {
  // Sanitise our signal handling state. Signals that were ignored by our
  // parent will also be ignored by us. We also inherit our parent's sigmask.
  sigset_t empty_signal_set;
  CHECK(0 == sigemptyset(&empty_signal_set));
  CHECK(0 == sigprocmask(SIG_SETMASK, &empty_signal_set, NULL));

  struct sigaction sigact;
  memset(&sigact, 0, sizeof(sigact));
  sigact.sa_handler = SIG_DFL;
  static const int signals_to_reset[] =
  { SIGHUP, SIGINT, SIGQUIT, SIGILL, SIGABRT, SIGFPE, SIGSEGV,
  SIGALRM, SIGTERM, SIGCHLD, SIGBUS, SIGTRAP };  // SIGPIPE is set below.
  for (unsigned i = 0; i < arraysize(signals_to_reset); i++) {
   CHECK(0 == sigaction(signals_to_reset[i], &sigact, NULL));
  }

  // Always ignore SIGPIPE.  We check the return value of write().
  CHECK(signal(SIGPIPE, SIG_IGN) != SIG_ERR);
 }

#endif // defined(OS_POSIX) && !defined(OS_IOS)

#if defined(USE_TCMALLOC)
 // static
bool MainRunner::GetAllocatorWasteSizeThunk(size_t* size) {
 size_t heap_size, allocated_bytes, unmapped_bytes;
 MallocExtension* ext = MallocExtension::instance();
 if (ext->GetNumericProperty("generic.heap_size", &heap_size) &&
  ext->GetNumericProperty("generic.current_allocated_bytes",
  &allocated_bytes) &&
  ext->GetNumericProperty("tcmalloc.pageheap_unmapped_bytes",
  &unmapped_bytes)) {
  *size = heap_size - allocated_bytes - unmapped_bytes;
  return true;
 }
 DCHECK(false);
 return false;
}

 // static
void MainRunner::GetStatsThunk(char* buffer, int buffer_length) {
 MallocExtension::instance()->GetStats(buffer, buffer_length);
}

 // static
void MainRunner::ReleaseFreeMemoryThunk() {
 MallocExtension::instance()->ReleaseFreeMemory();
}
#endif


MainRunner::MainRunner() : is_initialized_(false),
 is_shutdown_(false) {

}

MainRunner::~MainRunner() {
 if (is_initialized_ && !is_shutdown_)
  Shutdown();
}

int MainRunner::Initialize(const MainParams& params) {
  int exit_code = 0;

  base::EnableTerminationOnOutOfMemory();

#if defined(USE_TCMALLOC)
  // For tcmalloc, we need to tell it to behave like new.
  tc_set_new_mode(1);

  base::allocator::SetGetAllocatorWasteSizeFunction(
   GetAllocatorWasteSizeThunk);
  base::allocator::SetGetStatsFunction(GetStatsThunk);
  base::allocator::SetReleaseFreeMemoryFunction(ReleaseFreeMemoryThunk);
#endif
#if defined(OS_POSIX)
  SetupSignalHandlers();

  base::GlobalDescriptors* g_fds = base::GlobalDescriptors::GetInstance();
  g_fds->Set(kPrimaryIPCChannel,
   kPrimaryIPCChannel + base::GlobalDescriptors::kBaseDescriptor);
#endif
  is_initialized_ = true;

  hinstance_ = params.instance;

  exit_manager_.reset(new base::AtExitManager);

  base::CommandLine::Init(params.argc, params.argv);

  common::SetClient(&client_);
  // set only browser for now
  ClientInitializer::Set("", this);

  return exit_code;
 }

 int MainRunner::Run() {
  DCHECK(is_initialized_);
  DCHECK(!is_shutdown_);

  const base::CommandLine& command_line =
   *base::CommandLine::ForCurrentProcess();

  // default: command
  common::ProcessType type = common::PROCESS_TYPE_COMMAND;

  if (command_line.HasSwitch(switches::kKernelProcess)) {
   type = common::PROCESS_TYPE_KERNEL;
  }
  else if (command_line.HasSwitch(switches::kContainerProcess)) {
   type = common::PROCESS_TYPE_CONTAINER;
  }
  else if (command_line.HasSwitch(switches::kApplicationProcess)) {
   type = common::PROCESS_TYPE_APPLICATION;
  }

  common::MainParams main_params(command_line);
#if defined(OS_WIN)
  main_params.hInstance = hinstance_;
#endif
  return RunProcess(type, main_params);
 }

void MainRunner::Shutdown() {
 DCHECK(is_initialized_);
 DCHECK(!is_shutdown_);

 exit_manager_.reset(NULL);

 is_shutdown_ = true;
}

int MainRunner::RunProcess(
 common::ProcessType type,
 const common::MainParams& main_params) {

 if (type == common::PROCESS_TYPE_KERNEL) {
  return kernel::Main(main_params);
 }
 else if (type == common::PROCESS_TYPE_CONTAINER) {
  return container::Main(main_params);
 }
 else if (type == common::PROCESS_TYPE_COMMAND) {
  return command::Main(main_params);
 }
 else if (type == common::PROCESS_TYPE_APPLICATION) {
  return application::Main(main_params);
 }

 NOTREACHED() << "Unknown process type: " << type;
 return 1;
}

kernel::KernelClient* MainRunner::CreateKernelClient() {
  return g_kernel_client.Pointer();
}

//container::ContainerClient* MainRunner::CreateContainerClient() {
// return g_container_client.Pointer();
//}
//
//application::ApplicationClient* MainRunner::CreateApplicationClient() {
// return g_application_client.Pointer();
//}

}
