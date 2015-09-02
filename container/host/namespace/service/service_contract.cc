// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/service/service_contract.h"
#include "container/host/namespace/service/service_api.h"

namespace container {

ServiceContract::ServiceContract() {

}

ServiceContract::~ServiceContract() {

}

void ServiceContract::AddApi(ServiceApi* api) {
 apis_.push_back(api);
}

void ServiceContract::RemoveApi(ServiceApi* api) {
 apis_.erase(std::remove(apis_.begin(), apis_.end(), api), apis_.end());
}

}