// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_SERVICE_SERVICE_NETWORK_H__
#define CONTAINER_HOST_NAMESPACE_SERVICE_SERVICE_NETWORK_H__

#include "container/host/namespace/resource.h"

namespace container {

// All services are available through a network of services
// each peer has its "self" network, which is the services
// that are available only to the applications running locally
// than theres "public", which adds all social contacts
// making the services there available to everybody
// that are a social contact
// and then, theres the custom networks that the user can create
// to share some services only to a certain group of people

 class ServiceNetwork : public Resource {
public:
 ServiceNetwork(UUID id);
 ~ServiceNetwork();
private:

};

}

#endif