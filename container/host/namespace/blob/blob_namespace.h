// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_BLOB_BLOB_NAMESPACE_H__
#define CONTAINER_HOST_NAMESPACE_BLOB_BLOB_NAMESPACE_H__

#include "container/host/namespace/namespace.h"

namespace container {
class Blob;

// for blobs
class BlobNamespace : public Namespace {
public:
 BlobNamespace(UUID id);
 ~BlobNamespace() override;

 bool Put(Blob* blob);
 Blob* Get(const UUID& uuid);

private:

};

}

#endif