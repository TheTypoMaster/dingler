// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KERNEL_MAIN_RUNNER_H__
#define KERNEL_MAIN_RUNNER_H__

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "common/main_params.h"

namespace kernel {
class KernelMainLoop;
class NotificationServiceImpl;

class KernelMainRunner {
public:
 KernelMainRunner();
 ~KernelMainRunner();

 int Initialize(const common::MainParams& params);
 int Run();
 void Shutdown();

private:

 // True if we have started to initialize the runner.
 bool initialization_started_;
 // True if the runner has been shut down.
 bool is_shutdown_;

 scoped_ptr<KernelMainLoop> main_loop_;

 scoped_ptr<NotificationServiceImpl> notification_service_;

 DISALLOW_COPY_AND_ASSIGN(KernelMainRunner);
};

}

#endif
