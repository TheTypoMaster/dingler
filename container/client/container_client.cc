// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/client/container_client.h"

#include "container/common/container_messages.h"
#include "container/client/container_navigator.h"

namespace container {

ContainerClient::ContainerClient() {

}

ContainerClient::~ContainerClient() {

}

ContainerNavigator* ContainerClient::CreateNavigator() {

}

bool ContainerClient::Send(IPC::Message* msg) {

}

bool ContainerClient::OnMessageReceived(const IPC::Message& message) {

}

void ContainerClient::OnChannelConnected(int32 peer_pid) {

}

void ContainerClient::OnChannelError() {

}

void ContainerClient::OnBadMessageReceived(const IPC::Message& message) {

}

}
