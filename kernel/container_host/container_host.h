// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KERNEL_CONTAINER_CONTAINER_HOST_H__
#define KERNEL_CONTAINER_CONTAINER_HOST_H__

#include <vector>

#include "base/basictypes.h"
#include "container/common/uuid.h"
#include "common/status.h"
#include "kernel/container_host/container_args.h"
#include "kernel/container_host/container_state.h"
#include "kernel/container_host/running_pool.h"
#include "common/process_info.h"

namespace container {
class ContainerClient;
}

namespace kernel {
class ContainerManager;
class ContainerCommand;
class ContainerPeer;
class ContainerProcessHost;

class ContainerHost {
public:

 ContainerHost(ContainerManager* manager,
  std::string name);

 ~ContainerHost();

 const container::UUID& id();

 const std::string& name() const { return name_; }

 ContainerManager* manager() const { return manager_; }

 RunningPool* running_pool() { return &running_pool_; }

 ContainerProcessHost* process_host() const { return process_host_.get(); }

 container::ContainerClient* container_client() const { return container_client_.get(); }

 ContainerState state() const { return state_; }

 void set_state(ContainerState state) { state_ = state; }

 // Start the container
 status::Code Start(const ContainerStartArgs& args);
 // Stop the container
 status::Code Stop(const ContainerStopArgs& args);
 // Run a application or service inside the container
 status::Code RunProcess(const ContainerRunArgs& args);
 // Kill a running application or service (process)
 status::Code KillProcess(const ContainerKillArgs& args);
 // Get the list of running processes inside the container
 //common::ProcessIterator ListProcess(const ContainerListProcessArgs& args);

 // called by manager, give us a chance to hook into those events
 status::Code OnLoad(ContainerPeer* peer);
 status::Code OnUnload(ContainerPeer* peer);

private:
 
 ContainerManager* manager_;
 //cached id
 container::UUID id_;

 std::string name_;

 ContainerState state_;

 RunningPool running_pool_;

 scoped_ptr<ContainerProcessHost> process_host_;

 scoped_ptr<container::ContainerClient> container_client_;

 DISALLOW_COPY_AND_ASSIGN(ContainerHost);
};

}

#endif
