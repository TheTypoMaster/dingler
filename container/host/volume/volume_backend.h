// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_VOLUME_BACKEND_H__
#define CONTAINER_VOLUME_BACKEND_H__

#include "base/basictypes.h"

namespace container {
// the place in disk, where we take our volume datasets from
// this is our "repo"
class VolumeBackend {
public:
 VolumeBackend();
 ~VolumeBackend();

private:

 DISALLOW_COPY_AND_ASSIGN(VolumeBackend);
};

}


#endif