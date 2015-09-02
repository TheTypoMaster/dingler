// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KERNEL_CONTAINER_RUNNING_POOL_H__
#define KERNEL_CONTAINER_RUNNING_POOL_H__

#include "base/basictypes.h"
#include "base/memory/scoped_vector.h"

namespace kernel {
class RunningProcess;

class RunningPool {
public:
 RunningPool();
 ~RunningPool();

private:
 ScopedVector<RunningProcess> processes_;

 DISALLOW_COPY_AND_ASSIGN(RunningPool);
};

}

#endif