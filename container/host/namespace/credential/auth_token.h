// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_CREDENTIAL_AUTH_TOKEN_H__
#define CONTAINER_HOST_NAMESPACE_CREDENTIAL_AUTH_TOKEN_H__

#include "container/host/namespace/resource.h"

namespace container {
/*
 * Each time a user are using a given container
 * a auth token is generated for that session
 * associated by a given userid and all the users
 * actions are associated with a given auth token
 *
 * UserID´s can be given to applications, so each time
 * they are running, theres a associated auth-token with
 * each one of them.. a auth-token maybe can be 
 * revoked, cancelled, etc..
 */
class AuthToken : public Resource {
public:
 AuthToken(UUID uuid);
 ~AuthToken() override;
private:

 DISALLOW_COPY_AND_ASSIGN(AuthToken);
};

}

#endif
