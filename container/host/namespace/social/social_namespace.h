// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_SOCIAL_SOCIAL_NAMESPACE_H__
#define CONTAINER_HOST_NAMESPACE_SOCIAL_SOCIAL_NAMESPACE_H__

#include "container/host/namespace/namespace.h"

namespace container {

// A social filesystem: here you can make a network of friends
// in a asynchronous or synchronous way

class SocialNamespace : public Namespace {
public:
 SocialNamespace(UUID id);
 ~SocialNamespace() override;

private:

};

}

#endif