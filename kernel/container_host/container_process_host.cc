// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "kernel/container_host/container_process_host.h"

#include "container/common/container_messages.h"

namespace kernel {

ContainerProcessHost::ContainerProcessHost() {
 
}

ContainerProcessHost::~ContainerProcessHost() {

}

base::ProcessHandle ContainerProcessHost::GetHandle() const {
 return nullptr;
}

bool ContainerProcessHost::Send(IPC::Message* msg) {
 return false;
}

void ContainerProcessHost::OnProcessLaunched() {

}

void ContainerProcessHost::OnProcessLaunchFailed() {

}

bool ContainerProcessHost::OnMessageReceived(const IPC::Message& message) {
 return false;
}

void ContainerProcessHost::OnChannelConnected(int32 peer_pid) {

}

void ContainerProcessHost::OnChannelError() {

}

void ContainerProcessHost::OnBadMessageReceived(const IPC::Message& message) {

}

}
