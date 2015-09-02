// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/container.h"

#include "container/host/volume/volume_pool.h"
#include "container/host/volume/volume_drive.h"

namespace container {

Container::Container() {

}

Container::~Container() {

}

bool Container::Send(IPC::Message* msg) {
 return false;
}

bool Container::OnMessageReceived(const IPC::Message& message) {
 return false;
}

void Container::OnChannelConnected(int32 peer_pid) {

}

void Container::OnChannelError() {

}

void Container::OnBadMessageReceived(const IPC::Message& message) {

}

}