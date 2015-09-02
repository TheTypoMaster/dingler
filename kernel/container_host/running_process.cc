// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "kernel/container_host/running_process.h"

#include "kernel/application_host/application_process_host.h"

namespace kernel {

RunningProcess::RunningProcess(Runnable* owner) : owner_(owner) {
}

RunningProcess::~RunningProcess() {

}

status::Code RunningProcess::Init(const RunArgs& args) {
 return status::Ok;
}

status::Code RunningProcess::Shutdown(const KillArgs& args) {
 return status::Ok;
}

}