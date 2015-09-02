// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMON_CLIENT_H__
#define COMMON_CLIENT_H__

#include "base/basictypes.h"

namespace dingler {
class ClientInitializer;
}

namespace kernel {
class KernelClient;
}

namespace container {
class ContainerClient;
}

namespace application {
class ApplicationClient;
}

namespace common {

class Client {
public:
 Client();
 ~Client();

 kernel::KernelClient* kernel() const { return kernel_client_; }

 container::ContainerClient* container() const { return container_client_; }

 application::ApplicationClient* application() const { return application_client_; }

private:
 friend class dingler::ClientInitializer;

 kernel::KernelClient* kernel_client_;
 
 container::ContainerClient* container_client_;

 application::ApplicationClient* application_client_;

 DISALLOW_COPY_AND_ASSIGN(Client);
};

Client* GetClient();
void SetClient(Client* client);

}

#endif