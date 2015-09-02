// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "common/switches.h"

namespace switches {

const char kCommandProcess[] = "command";
const char kKernelProcess[] = "kernel";
const char kContainerProcess[] = "container";
const char kApplicationProcess[] = "application";

const char kIPCConnectionTimeout[] = "ipc-connection-timeout";
const char kKernelSubprocessPath[] = "kernel-subprocess-path";

// Don't send HTTP-Referer headers.
const char kNoReferrers[] = "no-referrers";

}