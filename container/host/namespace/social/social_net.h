// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_SOCIAL_SOCIAL_NET_H__
#define CONTAINER_SOCIAL_SOCIAL_NET_H__

#include "container/host/namespace/resource.h"

namespace container {
// TODO: define sync or async
// Work net, Friend Net, etc..
class SocialNet : public Resource {
public:
 SocialNet(UUID id);
 ~SocialNet() override;

private:
 DISALLOW_COPY_AND_ASSIGN(SocialNet);
};

}

#endif