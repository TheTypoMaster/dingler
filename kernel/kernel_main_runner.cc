// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/logging.h"
#include "kernel/kernel_main_runner.h"
#include "kernel/kernel_main_loop.h"
#include "kernel/notification_service_impl.h"
#include "third_party/bt/sqlite3.h"

bool g_exited_main_message_loop = false;

namespace kernel {

KernelMainRunner::KernelMainRunner(): 
  initialization_started_(false),
  is_shutdown_(false)  {

}

KernelMainRunner::~KernelMainRunner() {
 if (initialization_started_ && !is_shutdown_)
  Shutdown();
}

int KernelMainRunner::Initialize(const common::MainParams& params) {
 // initialize the sqlite environment
 sqlite3_initialize();

 notification_service_.reset(new NotificationServiceImpl);

 if (!initialization_started_) {
  initialization_started_ = true;

  main_loop_.reset(new KernelMainLoop(params));
  main_loop_->Init();
  main_loop_->EarlyInitialization();


  main_loop_->MainMessageLoopStart();
 }

 main_loop_->CreateStartupTasks();
 int result_code = main_loop_->result_code();
 if (result_code > 0)
  return result_code;

 // Return -1 to indicate no early termination.
 return -1;
}

int KernelMainRunner::Run() {
 DCHECK(initialization_started_);
 DCHECK(!is_shutdown_);
 main_loop_->RunMainMessageLoop();
 return main_loop_->result_code();
}

void KernelMainRunner::Shutdown() {
 DCHECK(initialization_started_);
 DCHECK(!is_shutdown_);

 g_exited_main_message_loop = true;

 main_loop_->ShutdownThreadsAndCleanUp();
 main_loop_.reset(nullptr);

 notification_service_.reset(nullptr);

 sqlite3_shutdown();

 is_shutdown_ = true;
}

}