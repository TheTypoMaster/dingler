// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_STATS_CONTAINER_H__
#define CONTAINER_HOST_STATS_CONTAINER_H__

#include "container/host/namespace/namespace.h"

namespace container {

// A stat filesystem: so we can have some
// basic measurements about the system

class StatsNamespace : public Namespace {
public:
 StatsNamespace(UUID id);
 ~StatsNamespace() override;

private:

};

}

#endif