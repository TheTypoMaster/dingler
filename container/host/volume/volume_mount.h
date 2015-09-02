// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_VOLUME_MOUNT_H__
#define CONTAINER_HOST_VOLUME_MOUNT_H__

#include "base/basictypes.h"
#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "container/common/uuid.h"

namespace container {
class Volume;
class VolumeMount {
public:
 VolumeMount(UUID uuid,
   const base::FilePath& path,
   Volume* volume);

 ~VolumeMount();

 const UUID& uuid() const { return uuid_; }
 // "/" , "/external"
 const base::FilePath& path() const { return path_; }

 Volume* volume() const { return volume_.get(); }

private:

 UUID uuid_;

 base::FilePath path_;
 
 scoped_ptr<Volume> volume_;

 DISALLOW_COPY_AND_ASSIGN(VolumeMount);
};

}

#endif