// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_SOCIAL_SOCIAL_CONTACT_H__
#define CONTAINER_HOST_NAMESPACE_SOCIAL_SOCIAL_CONTACT_H__

#include "container/host/namespace/resource.h"

namespace container {

class SocialContact : public Resource {
public:
 SocialContact(UUID id);
 ~SocialContact() override;

private:
 DISALLOW_COPY_AND_ASSIGN(SocialContact);
};

}

#endif