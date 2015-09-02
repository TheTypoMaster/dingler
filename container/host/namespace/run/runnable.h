// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_RUN_RUNNABLE_H__
#define CONTAINER_HOST_NAMESPACE_RUN_RUNNABLE_H__

#include "base/memory/scoped_ptr.h"
#include "container/host/namespace/resource.h"

namespace container {
class UserID;
 /* UserID´s can be given to applications, so each time
  * they are running, theres a associated auth token with
  * each one of them..a auth token maybe can be
  * revoked, cancelled, etc..
  */
class Runnable : public Resource {
public:
 Runnable(UUID id);
 ~Runnable() override;

 // associated user id.
 // apps are considered actors or agents, the same way
 // a user is. so apps are impersonated

 // On run a process is created and with it
 // a auth token, and is this auth token that defines
 // if a process or a user has access to a given resource
 const UUID& user_id() const { return user_; }

 void Run();

private:

 UUID user_;

 DISALLOW_COPY_AND_ASSIGN(Runnable);
};

}

#endif