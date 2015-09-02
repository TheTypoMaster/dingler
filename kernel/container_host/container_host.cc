// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <algorithm>

#include "kernel/container_host/container_host.h"

#include "kernel/container_host/container_application.h"
#include "kernel/container_host/container_service.h"
#include "kernel/container_host/container_process_host.h"
#include "kernel/container_host/running_process.h"
#include "container/client/container_client.h"

namespace kernel {

ContainerHost::ContainerHost(ContainerManager* manager,
 std::string name): 
  name_(std::move(name)) {

}

ContainerHost::~ContainerHost() {

}

const container::UUID& ContainerHost::id() {
 return id_;
}

status::Code ContainerHost::Start(const ContainerStartArgs& args) {
 return status::Ok;
}

status::Code ContainerHost::Stop(const ContainerStopArgs& args) {
 return status::Ok;
}

status::Code ContainerHost::RunProcess(const ContainerRunArgs& args) {
 return status::Ok;
}

status::Code ContainerHost::KillProcess(const ContainerKillArgs& args) {
 return status::Ok;
}

//common::ProcessIterator ContainerHost::ListProcess(const ContainerListProcessArgs& args) {
//  
//}

status::Code ContainerHost::OnLoad(ContainerPeer* peer) {
 return status::Ok;
}

status::Code ContainerHost::OnUnload(ContainerPeer* peer) {
 return status::Ok;
}

}
