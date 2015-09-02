// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/container/volume_resource.h"

namespace container {

VolumeResource::VolumeResource(UUID id) : Resource(id, ResourceType::Container) {

}

VolumeResource::~VolumeResource() {

}

}