// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <algorithm>

#include "container/host/volume/volume_mount.h"
#include "container/host/volume/volume.h"

namespace container {

VolumeMount::VolumeMount(UUID uuid,
 const base::FilePath& path,
 Volume* volume):
  uuid_(std::move(uuid)),
  path_(path),
  volume_(volume) {

}

VolumeMount::~VolumeMount() {

}

}