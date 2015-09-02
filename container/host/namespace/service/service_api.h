// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_SERVICE_SERVICE_API_H__
#define CONTAINER_HOST_NAMESPACE_SERVICE_SERVICE_API_H__

#include "container/host/namespace/resource.h"

namespace container {

enum class ServiceApiType {
 RPC_API,
};
/*
 * A service may have one or more api´s
 * each api is available with its 
 * public interfaces exposed.
 *
 * A service resource will list 
 * its registered api resources
 */
class ServiceApi : public Resource {
public:
 virtual ~ServiceApi();

 ServiceApiType api_type() const { return api_type_; }
protected:
 ServiceApi(UUID id, ServiceApiType api_type);
private:

 ServiceApiType api_type_;

 DISALLOW_COPY_AND_ASSIGN(ServiceApi);
};

}

#endif