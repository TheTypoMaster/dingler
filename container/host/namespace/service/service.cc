// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/service/service.h"

#include "container/host/namespace/service/service_contract.h"
#include "container/host/namespace/service/service_channel.h"

namespace container {

Service::Service(UUID uuid, ServiceType service_type) : 
 Resource(uuid, ResourceType::Service),
 service_type_(service_type), 
 state_(ServiceState::Init) {

}

Service::~Service() {

}

bool Service::Start() {
 // already started ?
 if (state_ == ServiceState::Started)
  return false;

 // try to bind to a socket port
 if (!channel_->Bind()) {
  state_ = ServiceState::Error;
  return false;
 }

 // now, try to listen
 if (!channel_->Listen()) {
  state_ = ServiceState::Error;
  return false;
 }

 state_ = ServiceState::Started;
 return true;
}

bool Service::Stop() {
 
 if (state_ == ServiceState::Started) {
  channel_->Close();
  state_ = ServiceState::Stopped;
  return true;
 }

 return false;
}

}