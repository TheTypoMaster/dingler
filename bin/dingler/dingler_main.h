// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BIN_DINGLER_MAIN_H__
#define BIN_DINGLER_MAIN_H__

#include "build/build_config.h"
#if defined(OS_WIN)
#include "base/win/win_util.h"
#endif

namespace dingler {

struct MainParams {
 int argc;
 const char** argv;
#if defined(OS_WIN)
 HINSTANCE instance;
#endif
};

int Main(const MainParams& params);

}

#endif
