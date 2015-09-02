// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "kernel/application_host/application_process_host.h"

#include "common/application_messages.h"

namespace kernel {

ApplicationProcessHost::ApplicationProcessHost() {

}

ApplicationProcessHost::~ApplicationProcessHost() {

}

base::ProcessHandle ApplicationProcessHost::GetHandle() const {
 return nullptr;
}

void ApplicationProcessHost::OnProcessLaunched() {

}

void ApplicationProcessHost::OnProcessLaunchFailed() {

}

bool ApplicationProcessHost::Send(IPC::Message* msg) {
 return false;
}

bool ApplicationProcessHost::OnMessageReceived(const IPC::Message& message) {
 return false;
}

void ApplicationProcessHost::OnChannelConnected(int32 peer_pid) {

}

void ApplicationProcessHost::OnChannelError() {

}

void ApplicationProcessHost::OnBadMessageReceived(const IPC::Message& message) {

}

}