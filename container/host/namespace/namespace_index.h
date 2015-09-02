// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_INDEX_H__
#define CONTAINER_HOST_NAMESPACE_INDEX_H__

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"

namespace container {
class NamespaceIndexDB;
struct NamespaceInode;

class NamespaceIndex {
public:
 NamespaceIndex();
 ~NamespaceIndex();

private:

 scoped_ptr<NamespaceIndexDB> db_;

 DISALLOW_COPY_AND_ASSIGN(NamespaceIndex);
};

}


#endif