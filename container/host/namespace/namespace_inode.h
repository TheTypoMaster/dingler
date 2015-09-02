// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_INODE_H__
#define CONTAINER_HOST_NAMESPACE_INODE_H__

#include <string>

#include "container/common/uuid.h"

namespace container {

struct NamespaceInode {
 // node name
 std::string  name;
 // the resource we are pointing to
 UUID resource;

 int          id;
 
 bool         root;
};

}

#endif