// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/credential/credential_namespace.h"

namespace container {
 
CredentialNamespace::CredentialNamespace(UUID uuid) :
 Namespace(uuid, NamespaceType::Credential) {

}
 
CredentialNamespace::~CredentialNamespace() {

}

bool CredentialNamespace::AddUser(UserID* user) {
 return false;
}

UserID* CredentialNamespace::LookupUser(const UUID& id) {
 return nullptr;
}

bool CredentialNamespace::RemoveUser(const UUID& id) {
 return false;
}

}