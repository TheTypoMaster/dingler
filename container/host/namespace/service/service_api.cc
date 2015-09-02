// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/service/service_api.h"

namespace container {

ServiceApi::ServiceApi(UUID id, ServiceApiType api_type) : 
 Resource(id, ResourceType::Service),
 api_type_(api_type){

}

 ServiceApi::~ServiceApi() {

}

}