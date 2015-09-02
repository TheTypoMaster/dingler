// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_CREDENTIAL_CREDENTIAL_NAMESPACE_H__
#define CONTAINER_HOST_NAMESPACE_CREDENTIAL_CREDENTIAL_NAMESPACE_H__

#include "container/host/namespace/namespace.h"

namespace container {
class UserID;
// A credential filesystem

// the userid´s have digital signatures
// the public key of a userid can be used
// as the routing id for the p2p net

class CredentialNamespace : public Namespace {
public:
 CredentialNamespace(UUID id);
 ~CredentialNamespace() override;

 bool AddUser(UserID* user);
 UserID* LookupUser(const UUID& uuid);
 bool RemoveUser(const UUID& uuid);

private:

};

}

#endif