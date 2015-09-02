// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/volume/volume_drive.h"

#include "container/common/container_messages.h"
#include "container/host/volume/volume_mount.h"

namespace container {

VolumeDrive::VolumeDrive() {

}

VolumeDrive::~VolumeDrive() {

}

// TODO: We must map/build the index when mouting the volume

status::Code VolumeDrive::MountVolume(Volume* volume,
 const base::FilePath& path, VolumeMount** out) {
 DCHECK(volume);

 auto mount = new VolumeMount(GenerateUUID(), path, volume);
 mount_table_.AddMount(mount);
 *out = mount;

 return status::Code::Ok;
}

status::Code VolumeDrive::UmountVolume(const UUID& mountid) {
 mount_table_.RemoveMount(mountid);
 return status::Code::Ok;
}

status::Code VolumeDrive::SetActiveVolume(const UUID& mountid) {
 return status::Code::Ok;
}

void VolumeDrive::MountIterator(VolumeMount* mount) {

}

}
