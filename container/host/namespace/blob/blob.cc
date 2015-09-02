// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/blob/blob.h"

namespace container {

Blob::Blob(UUID id) : Resource(id, ResourceType::Blob) {

}

Blob::~Blob() {

}

}