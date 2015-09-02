// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_VOLUME_H__
#define CONTAINER_VOLUME_H__

#include <string>

#include "base/basictypes.h"
#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "base/containers/hash_tables.h"
#include "common/status.h"
#include "container/common/uuid.h"

namespace container {
class Namespace;
class RootNamespace;
class VolumeBackend;
/* *
 * A Volume is a "database" of namespaces
 * each volume has a root namespace that organizes all others
 * A ContainerHost may have one or more Volumes
 * You can think of our Volumes as a Git Repo
 * With its own storage area(CAS) and filesystems
 */
class Volume {
public:
 Volume(UUID id, VolumeBackend* backend);
 ~Volume();

 const UUID& id() const { return id_; }

 RootNamespace* root() const { return root_.get(); }

private:
 
 UUID  id_;

 // loaded namespaces
 base::hash_map<std::string, Namespace> namespaces_;

 scoped_ptr<RootNamespace> root_;

 // the place where we take our volumes datasets from
 scoped_ptr<VolumeBackend> backend_;

 DISALLOW_COPY_AND_ASSIGN(Volume);
};

}

#endif