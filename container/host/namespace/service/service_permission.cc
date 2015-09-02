// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/service/service_permission.h"

namespace container {

ServicePermission::ServicePermission(UUID id): 
 Resource(id, ResourceType::Service) {

}

ServicePermission::~ServicePermission(){

}

}