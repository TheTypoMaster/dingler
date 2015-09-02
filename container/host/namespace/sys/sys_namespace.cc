// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/sys/sys_namespace.h"

namespace container {

SysNamespace::SysNamespace(UUID id) :
 Namespace(id, NamespaceType::Sys) {

}

 SysNamespace::~SysNamespace() {

}

}