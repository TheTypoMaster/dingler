// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_DRIVER_REQUEST_H__
#define CONTAINER_DRIVER_REQUEST_H__

#include "base/basictypes.h"
#include "container/driver/proto/header.h"

namespace container {

class Request {
public:
 Request();
 ~Request();

 InputCode code() const { return header_.input_code; }

 InputHeader* header() { return &header_; }

private:

 InputHeader header_;

 DISALLOW_COPY_AND_ASSIGN(Request);
};

}

#endif