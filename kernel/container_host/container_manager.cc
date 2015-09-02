// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "kernel/container_host/container_manager.h"

#include "kernel/container_host/container_host.h"
#include "kernel/container_host/container_peer.h"
#include "kernel/container_host/container_catalog.h"

namespace kernel {

ContainerManager::ContainerManager() {

}

ContainerManager::~ContainerManager() {

}

bool ContainerManager::Init() {
 return true;
}

void ContainerManager::Shutdown() {

}

status::Code ContainerManager::ExecuteCommand(const ContainerCommand& command) {
 return status::Ok;
}

status::Code ContainerManager::CreateContainer(const std::string& name, ContainerHost** out) {
 return status::Ok;
}

status::Code ContainerManager::DropContainer(const container::UUID& id) {
 return status::Ok;
}

status::Code ContainerManager::LoadContainer(ContainerPeer* peer, ContainerHost* container) {
 DCHECK(container);
 // give the container the chance to load
 auto res = container->OnLoad(peer);
 // cancel loading, by the container request
 if (res != status::Ok)
  return res;

 auto node = new ContainerNode{
  ContainerState::LOADING,
  base::Time::Now(),
  peer,
  container
 };

 nodes_[container->id()] = node;

 return status::Ok;
}

status::Code ContainerManager::UnloadContainer(ContainerPeer* peer, const container::UUID& id) {
 auto node = nodes_.at(id);
 if (!node) {
  return status::NotFound;
 }

 auto res = node->container->OnUnload(peer);
 // cancel the unload, by the container request
 if (res != status::Ok)
  return res;

 nodes_.erase(id);

 FreeNode(node);

 return status::Ok;
}

status::Code ContainerManager::FindContainer(const container::UUID& id, ContainerHost** out) {
 auto node = nodes_.at(id);
 if (!node) {
  *out = nullptr;
  return status::NotFound;
 }

 *out = node->container;

 return status::Ok;
}

status::Code ContainerManager::StartContainer(const container::UUID& id, const ContainerStartArgs& args) {
 return status::Ok;
}

status::Code ContainerManager::StopContainer(const container::UUID& id, const ContainerStopArgs& args) {
 return status::Ok;
}

status::Code ContainerManager::RunProcess(const container::UUID& id, const ContainerRunArgs& args) {
 return status::Ok;
}

status::Code ContainerManager::KillProcess(const container::UUID& id, const ContainerKillArgs& args) {
 return status::Ok;
}

status::Code ContainerManager::ListProcess(const container::UUID& id,
 const ContainerListProcessArgs& args,
 const common::ProcessIterator* out) {
 return status::Ok;
}

void ContainerManager::FreeNode(ContainerNode* ptr) {
 delete ptr->peer;
 delete ptr->container;
 delete ptr;
}

}