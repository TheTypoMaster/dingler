// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_DRIVER_RESPONSE_H__
#define CONTAINER_DRIVER_RESPONSE_H__

#include "base/basictypes.h"
#include "container/driver/proto/header.h"

namespace container {

class Response {
public:
 Response();
 ~Response();

private:

 OutputHeader header_;

 DISALLOW_COPY_AND_ASSIGN(Response);
};

}

#endif