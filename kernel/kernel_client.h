// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KERNEL_CLIENT_H__
#define KERNEL_CLIENT_H__

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/task_runner.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_vector.h"
#include "base/values.h"
#include "net/base/mime_util.h"
#include "net/cookies/canonical_cookie.h"
#include "net/url_request/url_request_interceptor.h"
#include "net/url_request/url_request_job_factory.h"
#include "common/client.h"
#if defined(OS_POSIX) && !defined(OS_MACOSX)
#include "base/posix/global_descriptors.h"
#endif

namespace kernel {

class KernelClient {
public:
 KernelClient();
 ~KernelClient();

 // Allows the embedder to change the default behavior of
 // KernelThread::PostAfterStartupTask to better match whatever
 // definition of "startup" the embedder has in mind. This may be
 // called on any thread.
 // Note: see related BrowserThread::PostAfterStartupTask.
 void PostAfterStartupTask(
  const tracked_objects::Location& from_here,
  const scoped_refptr<base::TaskRunner>& task_runner,
  const base::Closure& task);


private:

 DISALLOW_COPY_AND_ASSIGN(KernelClient);
};

}

#endif