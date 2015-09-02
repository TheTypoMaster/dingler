// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KERNEL_CONTAINER_RUNNABLE_H__
#define KERNEL_CONTAINER_RUNNABLE_H__

#include "container/common/uuid.h"
#include "common/status.h"

namespace base {
class FilePath;
}

namespace kernel {
class RunningProcess;

struct RunArgs {};
struct KillArgs {};

class Runnable {
public:
 virtual ~Runnable() {}
 
 virtual const base::FilePath& executable_path() const = 0;
 virtual const base::FilePath& workdir_path() const = 0;
 virtual const container::UUID& id() const = 0;
 virtual bool is_running() const = 0;
 virtual RunningProcess* GetRunningProcess() const = 0;
 virtual RunningProcess* Run(const RunArgs& args) = 0;
 virtual status::Code Kill(const KillArgs& args) = 0;
};

}

#endif