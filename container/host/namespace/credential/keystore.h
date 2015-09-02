// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_CREDENTIAL_KEYSTORE_H__
#define CONTAINER_HOST_NAMESPACE_CREDENTIAL_KEYSTORE_H__

#include "container/host/namespace/resource.h"

namespace container {
// crypto key keeper
class Keystore : public Resource {
public:
 Keystore(UUID id);
 ~Keystore() override;
private:

 DISALLOW_COPY_AND_ASSIGN(Keystore);
};

}

#endif