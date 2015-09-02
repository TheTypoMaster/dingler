// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "kernel/kernel_client.h"

#include "base/files/file_path.h"

namespace kernel {

KernelClient::KernelClient() {

}

KernelClient::~KernelClient() {
 
}

void KernelClient::PostAfterStartupTask(
 const tracked_objects::Location& from_here,
 const scoped_refptr<base::TaskRunner>& task_runner,
 const base::Closure& task) {
 task_runner->PostTask(from_here, task);
}

}