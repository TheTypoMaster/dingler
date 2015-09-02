// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_WALLET_WALLET_CONTAINER_H__
#define CONTAINER_HOST_NAMESPACE_WALLET_WALLET_CONTAINER_H__

#include "container/host/namespace/namespace.h"

namespace container {
// TODO: wallet should use a id, password
// from CredFS.
// prepare CredFS to manage private keys
// 
class WalletNamespace : public Namespace {
public:
 WalletNamespace(UUID uuid);
 ~WalletNamespace() override;

private:

};

}

#endif