// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KERNEL_CONTAINER_RUNNING_PROCESS_H__
#define KERNEL_CONTAINER_RUNNING_PROCESS_H__

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "common/status.h"

namespace kernel {
class Runnable;
class ApplicationProcessHost;
struct RunArgs;
struct KillArgs;

// A external running process. Can be a application or a service
// this guy control the ApplicationProcessHost that is the channel 
// to communicate with the foreign process
class RunningProcess {
public:
 RunningProcess(Runnable* owner);
 ~RunningProcess();

 ApplicationProcessHost* process_host() const { return process_host_.get(); }
 // get the runnable that owns us. a app or a service
 Runnable* owner() const { return owner_; }

 status::Code Init(const RunArgs& args);
 status::Code Shutdown(const KillArgs& args);

private:

 Runnable* owner_;

 scoped_ptr<ApplicationProcessHost> process_host_;

 DISALLOW_COPY_AND_ASSIGN(RunningProcess);
};

}

#endif