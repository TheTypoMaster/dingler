// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KERNEL_PROCESS_SUBTHREAD_H__
#define KERNEL_PROCESS_SUBTHREAD_H__

#include "kernel/kernel_thread.h"

namespace kernel {
class NotificationService;

class KernelProcessSubThread : public KernelThread {
public:
 explicit KernelProcessSubThread(KernelThread::ID id);
 ~KernelProcessSubThread() override;

protected:
 void Init() override;
 void CleanUp() override;

private:
 // These methods encapsulate cleanup that needs to happen on the IO thread
 // before we call the embedder's CleanUp function.
 void IOThreadPreCleanUp();

 // Each specialized thread has its own notification service.
 scoped_ptr<NotificationService> notification_service_;

 DISALLOW_COPY_AND_ASSIGN(KernelProcessSubThread);
};

}

#endif