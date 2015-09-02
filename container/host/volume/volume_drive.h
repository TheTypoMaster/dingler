// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_VOLUME_VOLUME_DRIVE_H__
#define CONTAINER_HOST_VOLUME_VOLUME_DRIVE_H__

#include <vector>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/files/file_path.h"
#include "common/status.h"
#include "container/host/volume/volume_mount_table.h"

namespace container {
class VolumeMount;
class Volume;

class VolumeDrive {
public:
 VolumeDrive();
 ~VolumeDrive();

 status::Code MountVolume(Volume* volume,
  const base::FilePath& path, VolumeMount** out);

 status::Code UmountVolume(const UUID& mountid);
 
 // despite the fact that we can have more than one volume
 // mounted here, only one volume is the <active> volume
 // we can use this feature to update a volume for instance
 // while putting a temp clone in place
 status::Code SetActiveVolume(const UUID& mountid);

private:

 void MountIterator(VolumeMount* mount);

 VolumeMountTable mount_table_;

 DISALLOW_COPY_AND_ASSIGN(VolumeDrive);
};

}

#endif
