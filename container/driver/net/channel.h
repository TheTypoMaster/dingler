// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_DRIVER_CHANNEL_H__
#define CONTAINER_DRIVER_CHANNEL_H__

#include "base/basictypes.h"

namespace container {

// a connection channel. a conn may have one or more channels
class Channel {
public:
 Channel();
 ~Channel();

private:

 DISALLOW_COPY_AND_ASSIGN(Channel);
};

}

#endif