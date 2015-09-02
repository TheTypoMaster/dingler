// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMAND_SCREEN_BUFFER_H__
#define COMMAND_SCREEN_BUFFER_H__

#include "base/basictypes.h"

#if defined(OS_WIN)
#include <windows.h>
#endif

namespace command {

struct Buffer {
#if defined(OS_WIN)
HANDLE  handle;
Buffer() : handle(INVALID_HANDLE_VALUE) {}
Buffer(HANDLE h) : handle(h) {}

#endif
};

typedef Buffer InputBuffer;
typedef Buffer OutputBuffer;

}

#endif