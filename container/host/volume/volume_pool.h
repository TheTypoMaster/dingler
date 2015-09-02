// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_VOLUME_POOL_H__
#define CONTAINER_VOLUME_POOL_H__

#include "base/basictypes.h"
#include "base/files/file_path.h"
#include "container/common/uuid.h"

namespace container {
class Volume;
 /*
  * The CAS storage for volumes
  */
class VolumePool {
public:
 VolumePool(base::FilePath root_path);
 ~VolumePool();

 const base::FilePath& root_path() const { return root_path_; }

 Volume* OpenVolume(const UUID& uuid);
 bool DeleteVolume(const UUID& uuid);
 // todo: list volumes

private:

 base::FilePath root_path_;

 DISALLOW_COPY_AND_ASSIGN(VolumePool);
};

}

#endif