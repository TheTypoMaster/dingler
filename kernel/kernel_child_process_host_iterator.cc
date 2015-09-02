// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Copyright 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "kernel/kernel_child_process_host_iterator.h"

#include "base/logging.h"
#include "common/process_type.h"
#include "kernel/kernel_child_process_host.h"
#include "kernel/kernel_thread.h"

namespace kernel {

 KernelChildProcessHostIterator::KernelChildProcessHostIterator()
    : all_(true), process_type_(common::PROCESS_TYPE_UNKNOWN) {
 CHECK(KernelThread::CurrentlyOn(KernelThread::IO)) <<
      "KernelChildProcessHostIterator must be used on the IO thread.";
 iterator_ = KernelChildProcessHost::GetIterator()->begin();
}

KernelChildProcessHostIterator::KernelChildProcessHostIterator(int type)
    : all_(false), process_type_(type) {
 CHECK(KernelThread::CurrentlyOn(KernelThread::IO)) <<
      "KernelChildProcessHostIterator must be used on the IO thread.";
 DCHECK_NE(common::PROCESS_TYPE_APPLICATION, type) <<
      "KernelChildProcessHostIterator doesn't work for renderer processes; "
      "try RenderProcessHost::AllHostsIterator() instead.";
 iterator_ = KernelChildProcessHost::GetIterator()->begin();
  if (!Done() && (*iterator_)->GetData().process_type != process_type_)
    ++(*this);
}

KernelChildProcessHostIterator::~KernelChildProcessHostIterator() {
}

bool KernelChildProcessHostIterator::operator++() {
  CHECK(!Done());
  do {
    ++iterator_;
    if (Done())
      break;

    if (!all_ && (*iterator_)->GetData().process_type != process_type_)
      continue;

    return true;
  } while (true);

  return false;
}

bool KernelChildProcessHostIterator::Done() {
 return iterator_ == KernelChildProcessHost::GetIterator()->end();
}

const ChildProcessData& KernelChildProcessHostIterator::GetData() {
  CHECK(!Done());
  return (*iterator_)->GetData();
}

bool KernelChildProcessHostIterator::Send(IPC::Message* message) {
  CHECK(!Done());
  return (*iterator_)->Send(message);
}

KernelChildProcessHostDelegate*
KernelChildProcessHostIterator::GetDelegate() {
  return (*iterator_)->delegate();
}

}  // namespace kernel
