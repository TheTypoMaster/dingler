// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "kernel/kernel_process_subthread.h"

#include "base/threading/thread_restrictions.h"
#include "kernel/notification_service.h"
#include "kernel/notification_service_impl.h"
#include "kernel/kernel_thread.h"
#include "kernel/kernel_child_process_host.h"

namespace kernel {

KernelProcessSubThread::KernelProcessSubThread(KernelThread::ID id): 
 KernelThread(id) {

}

KernelProcessSubThread::~KernelProcessSubThread() {

}

void KernelProcessSubThread::Init() {
 notification_service_.reset(new NotificationServiceImpl());

 KernelThread::Init();

 if (KernelThread::CurrentlyOn(KernelThread::IO)) {
  // Though this thread is called the "IO" thread, it actually just routes
  // messages around; it shouldn't be allowed to perform any blocking disk
  // I/O.
  base::ThreadRestrictions::SetIOAllowed(false);
  base::ThreadRestrictions::DisallowWaiting();
 }
}

void KernelProcessSubThread::CleanUp() {
 if (KernelThread::CurrentlyOn(KernelThread::IO))
  IOThreadPreCleanUp();

 KernelThread::CleanUp();

 notification_service_.reset();
}

void KernelProcessSubThread::IOThreadPreCleanUp() {
 KernelChildProcessHost::TerminateAll();
}

}