// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/blob/blob_namespace.h"

namespace container {

BlobNamespace::BlobNamespace(UUID uuid) :
 Namespace(uuid, NamespaceType::Blob) {

}

BlobNamespace::~BlobNamespace() {

}

bool BlobNamespace::Put(Blob* blob) {
 return false;
}

Blob* BlobNamespace::Get(const UUID& id) {
 return nullptr;
}

}