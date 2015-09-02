// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_VOLUME_DATASET_H__
#define CONTAINER_VOLUME_DATASET_H__

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "db/context.h"

namespace container {
/*
 * Each Dataset is backed up by a sqlite db file
 * so depending on the layout of the data into the filesystem
 * the data may be 1-1 over dataset, eg. blobs
 * or 1-many in case of small structured data
 *
 * We will define that on the DB file header
 * which this dataset represents, and will manage
 */
class VolumeDataset {
public:
 VolumeDataset();
 ~VolumeDataset();

private:

 scoped_ptr<db::Context> db_;
 
 DISALLOW_COPY_AND_ASSIGN(VolumeDataset);
};

}

#endif