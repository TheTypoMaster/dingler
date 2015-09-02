// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_THREAD_H__
#define CONTAINER_THREAD_H__

#include "base/basictypes.h"

namespace container {
// we need 3 threads actually: Main, IO and Job (or Worker)
class ContainerThread {
public:
 ContainerThread();
 ~ContainerThread();
 
private:
 DISALLOW_COPY_AND_ASSIGN(ContainerThread);
};

}

#endif
