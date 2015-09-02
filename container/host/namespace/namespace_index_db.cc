// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/namespace_index_db.h"

namespace container {
 
NamespaceIndexDB::NamespaceIndexDB() {

}

NamespaceIndexDB::~NamespaceIndexDB() {

}

bool NamespaceIndexDB::InsertInode(NamespaceInode* node) {
 return false;
}

NamespaceInode* NamespaceIndexDB::LookupInode(int id) {
 return nullptr;
}

bool NamespaceIndexDB::DeleteInode(int id) {
 return false;
}

}