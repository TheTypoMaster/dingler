// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_CRED_USERID_H__
#define CONTAINER_HOST_NAMESPACE_CRED_USERID_H__

#include "container/host/namespace/resource.h"

namespace container {

// represents a user available to the container
// user´s have a digital signature enforced

class UserID : public Resource {
public:
 UserID(UUID id);
 ~UserID() override;
private:

};

}

#endif