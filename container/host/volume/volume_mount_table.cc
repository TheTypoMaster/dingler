// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/volume/volume_mount_table.h"

#include "base/logging.h"
#include "container/host/volume/volume_mount.h"

namespace container {

VolumeMountTable::VolumeMountTable() {

}

VolumeMountTable::~VolumeMountTable() {

}

void VolumeMountTable::AddMount(VolumeMount* mount) {
 DCHECK(mount);
 mounts_[mount->uuid()] = mount;
}

VolumeMount* VolumeMountTable::LookupMount(const UUID& id) {
 return mounts_.at(id);
}

void VolumeMountTable::Iterate(const VolumeMountTable::Iterator& iterator) {
 for (auto it = mounts_.begin(); it != mounts_.end(); ++it) {
  iterator.Run(it->second);
 }
}

void VolumeMountTable::RemoveMount(const UUID& id) {
 mounts_.erase(id);
}

}