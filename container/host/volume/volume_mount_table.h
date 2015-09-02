// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_VOLUME_MOUNT_TABLE_H__
#define CONTAINER_VOLUME_MOUNT_TABLE_H__

#include "base/basictypes.h"
#include "base/containers/hash_tables.h"
#include "base/callback.h"
#include "container/common/uuid.h"

namespace container {
class VolumeMount;

class VolumeMountTable {
public:
 typedef base::Callback<void(VolumeMount* mount)> Iterator;

 VolumeMountTable();
 ~VolumeMountTable();

 void AddMount(VolumeMount* mount);
 VolumeMount* LookupMount(const UUID& id);
 void Iterate(const Iterator& iterator);
 void RemoveMount(const UUID& id);

private:

 base::hash_map<UUID, VolumeMount *> mounts_;

 DISALLOW_COPY_AND_ASSIGN(VolumeMountTable);
};

}

#endif