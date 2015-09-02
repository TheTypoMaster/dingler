// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/social/social_contact.h"

namespace container {

SocialContact::SocialContact(UUID id) : Resource(id, ResourceType::Social) {

}

SocialContact::~SocialContact() {
}

}