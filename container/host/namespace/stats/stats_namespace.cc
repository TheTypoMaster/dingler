// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/stats/stats_namespace.h"

namespace container {
 
StatsNamespace::StatsNamespace(UUID id) :
 Namespace(id, NamespaceType::Stats) {

}
 
StatsNamespace::~StatsNamespace() {

}

}