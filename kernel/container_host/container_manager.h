// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KERNEL_CONTAINER_CONTAINER_MANAGER_H__
#define KERNEL_CONTAINER_CONTAINER_MANAGER_H__

#include <vector>
#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_vector.h"
#include "base/containers/hash_tables.h"
#include "base/time/time.h"
#include "common/status.h"
#include "common/container_info.h"
#include "container/common/uuid.h"
#include "common/process_info.h"
#include "kernel/container_host/container_args.h"
#include "kernel/container_host/container_state.h"

namespace kernel {
class ContainerPeer;
class ContainerCatalog;
class ContainerCommand;
class ContainerHost;

// The Container Manager
class ContainerManager {
public:

 struct ContainerNode {
  ContainerState state;
  base::Time loaded;
  // owned, on-heap, manually freed
  ContainerPeer* peer;
  // owned, on-heap, manually freed
  ContainerHost* container;
 };

 ContainerManager();
 ~ContainerManager();

 bool Init();
 void Shutdown();

 ContainerCatalog* catalog() const { return catalog_.get(); }

 // universal entry to execute any command
 status::Code ExecuteCommand(const ContainerCommand& command);

 status::Code CreateContainer(const std::string& name, ContainerHost** out);
 status::Code DropContainer(const container::UUID& id);
 status::Code LoadContainer(ContainerPeer* peer, ContainerHost* container);
 status::Code UnloadContainer(ContainerPeer* peer, const container::UUID& id);
 status::Code FindContainer(const container::UUID& id, ContainerHost** out);
 status::Code StartContainer(const container::UUID& id, const ContainerStartArgs& args);
 status::Code StopContainer(const container::UUID& id, const ContainerStopArgs& args);
 status::Code RunProcess(const container::UUID& id, const ContainerRunArgs& args);
 status::Code KillProcess(const container::UUID& id, const ContainerKillArgs& args);
 status::Code ListProcess(const container::UUID& id,
  const ContainerListProcessArgs& args, 
  const common::ProcessIterator* out);

private:

 void FreeNode(ContainerNode* ptr);

 scoped_ptr<ContainerCatalog> catalog_;

 base::hash_map<container::UUID, ContainerNode *> nodes_;
 
 DISALLOW_COPY_AND_ASSIGN(ContainerManager);
};

}

#endif