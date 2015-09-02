// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_WALLET_WALLET_H__
#define CONTAINER_HOST_NAMESPACE_WALLET_WALLET_H__

#include "container/host/namespace/resource.h"

namespace container {

class Wallet : public Resource {
public:
 Wallet(UUID id);
 ~Wallet() override;
private:

};

}

#endif