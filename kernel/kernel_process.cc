// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "kernel/kernel_process.h"

#include "base/message_loop/message_loop.h"
#include "base/path_service.h"
#include "base/logging.h"
#include "base/trace_event/trace_event.h"
#include "base/prefs/pref_service.h"
#include "base/prefs/pref_registry.h"
#include "base/prefs/pref_service_factory.h"
#include "base/prefs/pref_store.h"
#include "base/prefs/pref_filter.h"
#include "base/prefs/json_pref_store.h"
#include "base/prefs/default_pref_store.h"
#include "kernel/container_host/container_manager.h"
#include "kernel/prefs/user_prefs.h"
#include "kernel/prefs/kernel_prefs.h"
#include "kernel/prefs/command_line_pref_store.h"
#include "kernel/prefs/pref_registry_syncable.h"
#include "kernel/io_thread.h"
#include "common/constants.h"

namespace kernel {

namespace {

void HandleReadError(PersistentPrefStore::PrefReadError error) {
}

void PrepareFactory(base::PrefServiceFactory* factory,
 scoped_refptr<PersistentPrefStore> user_pref_store,
 bool async) {
 factory->set_async(async);
 factory->set_command_line_prefs(
  make_scoped_refptr(
  new CommandLinePrefStore(base::CommandLine::ForCurrentProcess())));
 factory->set_read_error_callback(base::Bind(&HandleReadError));
 factory->set_user_prefs(user_pref_store);
}

scoped_ptr<PrefService> CreateProfilePrefs(
 const base::FilePath& profile_path,
 base::SequencedTaskRunner* pref_io_task_runner,
 const scoped_refptr<PrefRegistry>& pref_registry) {
 TRACE_EVENT0("kernel", "::CreateProfilePrefs");

  base::PrefServiceFactory factory;

 scoped_refptr<PersistentPrefStore> user_pref_store(
  new JsonPrefStore(profile_path.Append(constants::kPreferencesFilename),
  pref_io_task_runner,
  scoped_ptr<PrefFilter>()));

 PrepareFactory(&factory,
  user_pref_store,
  true);

 scoped_ptr<PrefService> pref_service =
  factory.Create(pref_registry.get());

 return pref_service.Pass();
}

}

KernelProcess* g_kernel_process = nullptr;

// static
KernelProcess* KernelProcess::current() {
 return g_kernel_process;
}

KernelProcess::KernelProcess(const base::FilePath& path, 
 base::SequencedTaskRunner* local_state_task_runner,
 const common::MainParams& main_params): 
  main_params_(main_params),
  module_ref_count_(0),
  did_start_(false),
  local_state_task_runner_(local_state_task_runner),
  path_(path),
  pref_registry_(new PrefRegistrySyncable) {
 
 g_kernel_process = this;

}

KernelProcess::~KernelProcess() {

}

ContainerManager* KernelProcess::container_manager() const {
 DCHECK(CalledOnValidThread());
 return container_manager_.get(); 
}

IOThread* KernelProcess::io_thread() const {
 DCHECK(CalledOnValidThread());
 return io_thread_.get();
}

void KernelProcess::PreCreateThreads() {
 
 prefs_ = CreateProfilePrefs(
  path_,
  local_state_task_runner_.get(),
  pref_registry_).Pass();

 RegisterLocalState(pref_registry_.get());

 io_thread_.reset(new IOThread());
}

void KernelProcess::PreMainMessageLoopRun() {
 auto manager = new ContainerManager();
 if (!manager->Init()) {
  LOG(ERROR) << "Problem loading the Container Manager";
 }

 container_manager_.reset(manager);

 UserPrefs::Set(this, prefs_.get());
}

void KernelProcess::StartTearDown() {
 container_manager_->Shutdown();
}

void KernelProcess::PostMainMessageLoopRun() {

}

void KernelProcess::PostDestroyThreads() {
 io_thread_.reset();
}

void KernelProcess::Shutdown() {
 DCHECK(base::MessageLoop::current());
 // todo: fix how we can exit clean and properly
 base::MessageLoop::current()->Quit();
}

unsigned int KernelProcess::AddRefModule() {
 DCHECK(CalledOnValidThread());
 did_start_ = true;
 module_ref_count_++;
 return module_ref_count_;
}

unsigned int KernelProcess::ReleaseModule() {
 DCHECK(CalledOnValidThread());
 DCHECK_NE(0u, module_ref_count_);
 module_ref_count_--;
 return module_ref_count_;
}

bool KernelProcess::IsShuttingDown() {
 return false;
}


}