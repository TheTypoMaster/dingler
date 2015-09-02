// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Copyright 2013 The Chromium Authors. All rights reserved.
// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "kernel/kernel_child_process_observer.h"

#include "kernel/kernel_child_process_host.h"

namespace kernel {

// static
void KernelChildProcessObserver::Add(KernelChildProcessObserver* observer) {
  KernelChildProcessHost::AddObserver(observer);
}

// static
void KernelChildProcessObserver::Remove(
  KernelChildProcessObserver* observer) {
  KernelChildProcessHost::RemoveObserver(observer);
}

}  // namespace kernel
