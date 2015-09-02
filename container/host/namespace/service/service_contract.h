// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_SERVICE_SERVICE_CONTRACT_H__
#define CONTAINER_HOST_NAMESPACE_SERVICE_SERVICE_CONTRACT_H__

#include "base/basictypes.h"
#include "base/memory/scoped_vector.h"

namespace container {
class ServiceApi;

class ServiceContract {
public:
 ServiceContract();
 ~ServiceContract();

 const ScopedVector<ServiceApi>& ListApi() const {
  return apis_;
 }
 void AddApi(ServiceApi* api);
 void RemoveApi(ServiceApi* api);

private:

 ScopedVector<ServiceApi> apis_;

 DISALLOW_COPY_AND_ASSIGN(ServiceContract);
};

}

#endif