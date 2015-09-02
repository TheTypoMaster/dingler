// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <algorithm>

#include "container/host/namespace/resource.h"

namespace container {

Resource::Resource(UUID id, ResourceType type) :
  id_(std::move(id)), 
  type_(type),
  special_(SpecialMode::Ordinary),
  readonly_(false) {

}

Resource::Resource(UUID id, ResourceType type, SpecialMode special_mode) :
 id_(std::move(id)),
 type_(type),
 special_(special_mode),
 readonly_(false) {

}

Resource::~Resource() {

}

}