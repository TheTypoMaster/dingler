// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_SERVICE_SERVICE_H__
#define CONTAINER_HOST_NAMESPACE_SERVICE_SERVICE_H__

#include "base/memory/scoped_ptr.h"
#include "container/host/namespace/resource.h"

namespace container {
class ServiceContract;
class ServiceChannel;

enum class ServiceType {
 RPC,
};

enum class ServiceState {
 Init,
 Initialized,
 Started,
 Stopped,
 Shutdown,
 Error,
};

class Service : public Resource {
public:
 virtual ~Service();

 ServiceType service_type() const { return service_type_; }

 ServiceState state() const { return state_; }

 ServiceChannel* channel() const { return channel_.get(); }

 ServiceContract* contract() const { return contract_.get(); }

 bool Start();
 bool Stop();

 virtual void Init() = 0;
 virtual void Shutdown() = 0;

protected:
 Service(UUID id, ServiceType service_type);

 ServiceState state_;

 scoped_ptr<ServiceChannel> channel_;

 scoped_ptr<ServiceContract> contract_;

private:

 ServiceType service_type_;

 DISALLOW_COPY_AND_ASSIGN(Service);
};

}

#endif