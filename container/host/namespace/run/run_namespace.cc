// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/run/run_namespace.h"

namespace container {

RunNamespace::RunNamespace(UUID uuid) :
 Namespace(uuid, NamespaceType::Run) {

}

RunNamespace::~RunNamespace() {

}

}