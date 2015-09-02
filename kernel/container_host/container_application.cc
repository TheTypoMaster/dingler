// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "kernel/container_host/container_application.h"

#include "base/logging.h"
#include "kernel/container_host/running_process.h"

namespace kernel {

ContainerApplication::ContainerApplication(container::UUID uuid) : id_(std::move(uuid)) {

}

ContainerApplication::~ContainerApplication() {

}

bool ContainerApplication::is_running() const {
 // if theres a process launched, we are running
 return process_.get() != nullptr;
}

RunningProcess* ContainerApplication::GetRunningProcess() const {
 return process_.get();
}

RunningProcess* ContainerApplication::Run(const RunArgs& args) {
 auto proc = new RunningProcess(this);
 
 // actually launch it
 if (proc->Init(args) != status::Ok) {
  delete proc;
  return nullptr;
 }

 process_.reset(proc);
 return proc;
}

status::Code ContainerApplication::Kill(const KillArgs& args) {
 if (!process_.get()) {
  return status::NotRunning;
 }
 
 auto res = process_->Shutdown(args);
 if (res != status::Ok) {
  return res;
 }

 process_.reset();

 return status::Ok;
}

}