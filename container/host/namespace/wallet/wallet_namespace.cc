// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/wallet/wallet_namespace.h"

namespace container {

WalletNamespace::WalletNamespace(UUID id) :
 Namespace(id, NamespaceType::Wallet) {

}

 WalletNamespace::~WalletNamespace() {

}

}