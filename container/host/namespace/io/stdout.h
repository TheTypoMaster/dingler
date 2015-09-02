// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_IO_STDOUT_H__
#define CONTAINER_HOST_NAMESPACE_IO_STDOUT_H__

#include "container/host/namespace/resource.h"

namespace container {

class STDOUT : public Resource {
public:
 STDOUT(UUID id);
 ~STDOUT() override;
private:

};

}

#endif