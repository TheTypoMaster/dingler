// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <algorithm>

#include "container/host/volume/volume_pool.h"

namespace container {

VolumePool::VolumePool(base::FilePath root_path) :
 root_path_(std::move(root_path)){

}

VolumePool::~VolumePool() {

}

Volume* VolumePool::OpenVolume(const UUID& uuid) {
 return nullptr;
}

bool VolumePool::DeleteVolume(const UUID& uuid) {
 return false;
}

}