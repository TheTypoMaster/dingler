// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/uuid/uuid_namespace.h"

namespace container {

UUIDNamespace::UUIDNamespace(UUID id) :
  Namespace(id, NamespaceType::UUID) {

}

 UUIDNamespace::~UUIDNamespace() {

}

}