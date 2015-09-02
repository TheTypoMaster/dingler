// Copyright 2013 The Chromium Authors. All rights reserved.
// Copyright 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KERNEL_KERNEL_CHILD_PROCESS_OBSERVER_H_
#define KERNEL_KERNEL_CHILD_PROCESS_OBSERVER_H_

namespace kernel {

struct ChildProcessData;

// An observer API implemented by classes which are interested in browser child
// process events. Note that render processes cannot be observed through this
// interface; use RenderProcessHostObserver instead.
class KernelChildProcessObserver {
 public:
  // Called when a child process host has connected to a child process.
  virtual void KernelChildProcessHostConnected(const ChildProcessData& data) {}

  // Called after a ChildProcessHost is disconnected from the child process.
  virtual void KernelChildProcessHostDisconnected(
      const ChildProcessData& data) {}

  // Called when a child process disappears unexpectedly as a result of a crash.
  virtual void KernelChildProcessCrashed(const ChildProcessData& data) {}

  // Called when an instance of a particular child is created in a page. If one
  // page contains several regions rendered by the same child, this will be
  // called once for each region during the page load.
  virtual void KernelChildProcessInstanceCreated(
      const ChildProcessData& data) {}

 protected:
  // The observer can be destroyed on any thread.
  virtual ~KernelChildProcessObserver() {}

  static void Add(KernelChildProcessObserver* observer);
  static void Remove(KernelChildProcessObserver* observer);
};

}  // namespace kernel

#endif  // KERNEL_KERNEL_CHILD_PROCESS_OBSERVER_H_
