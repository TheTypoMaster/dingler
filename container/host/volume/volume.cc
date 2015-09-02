// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <algorithm>

#include "container/host/volume/volume.h"

#include "container/host/namespace/namespace.h"
#include "container/host/namespace/root/root_namespace.h"
#include "container/host/volume/volume_backend.h"

namespace container {

Volume::Volume(UUID id, VolumeBackend* backend) : id_(std::move(id)),
  backend_(backend){

}

Volume::~Volume() {

}

}