// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_INDEX_DB_H__
#define CONTAINER_HOST_NAMESPACE_INDEX_DB_H__

#include "base/basictypes.h"

namespace container {
struct NamespaceInode;

class NamespaceIndexDB {
public:
 NamespaceIndexDB();
 ~NamespaceIndexDB();

 bool InsertInode(NamespaceInode* node);
 NamespaceInode* LookupInode(int id);
 bool DeleteInode(int id);

private:

 DISALLOW_COPY_AND_ASSIGN(NamespaceIndexDB);
};

}

#endif
