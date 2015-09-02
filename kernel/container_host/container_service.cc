// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <algorithm>

#include "kernel/container_host/container_service.h"

#include "base/logging.h"
#include "kernel/container_host/running_process.h"

namespace kernel {

ContainerService::ContainerService(container::UUID uuid) : id_(std::move(uuid)) {

}

ContainerService::~ContainerService() {

}

bool ContainerService::is_running() const {
 return process_.get() != nullptr;
}

RunningProcess* ContainerService::GetRunningProcess() const {
 return process_.get(); 
}

RunningProcess* ContainerService::Run(const RunArgs& args)  {
 auto proc = new RunningProcess(this);
 
 if (proc->Init(args) != status::Ok) {
  delete proc;
  return nullptr;
 }

 process_.reset(proc);
 return proc;
}

status::Code ContainerService::Kill(const KillArgs& args) {
 if (!process_.get()) {
  return status::Code::NotRunning;
 }

 auto res = process_->Shutdown(args);
 if (res != status::Ok) {
  return res;
 }

 process_.reset();

 return status::Ok;
}

}