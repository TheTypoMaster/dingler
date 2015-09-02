// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KERNEL_CONTAINER_CONTAINER_SERVICE_H__
#define KERNEL_CONTAINER_CONTAINER_SERVICE_H__

#include "base/basictypes.h"
#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "container/common/uuid.h"
#include "kernel/container_host/runnable.h"

namespace kernel {

// A public container service
class ContainerService : public Runnable {
public:
 ContainerService(container::UUID uuid);
 ~ContainerService() override;
 
 // Runnable overrides
 const base::FilePath& executable_path() const override { return executable_path_; }
 const base::FilePath& workdir_path() const override { return workdir_path_; }
 const container::UUID& id() const override { return id_; }
 bool is_running() const override;
 RunningProcess* GetRunningProcess() const override;
 RunningProcess* Run(const RunArgs& args) override;
 status::Code Kill(const KillArgs& args) override;

private:

 container::UUID id_;

 base::FilePath executable_path_;

 base::FilePath workdir_path_;

 scoped_ptr<RunningProcess> process_;

 DISALLOW_COPY_AND_ASSIGN(ContainerService);
};

}

#endif