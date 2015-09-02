// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "kernel/container_host/container_catalog.h"

#include "db/context.h"

namespace kernel {

ContainerCatalog::ContainerCatalog() {
}

ContainerCatalog::~ContainerCatalog() {
}

status::Code ContainerCatalog::CreateContainer(const std::string& name,
 Container** out) {

 return status::Ok;
}

status::Code ContainerCatalog::LoadContainer(const std::string& name,
 Container** out) {
 return status::Ok;
}

status::Code ContainerCatalog::DropContainer(const std::string& name) {
 return status::Ok;
}

}