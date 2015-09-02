// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMON_MAIN_PARAMS_H__
#define COMMON_MAIN_PARAMS_H__

#include "base/callback_forward.h"
#include "base/command_line.h"
#if defined(OS_WIN)
#include "base/win/win_util.h"
#endif

namespace common {

struct MainParams {
 explicit MainParams(const base::CommandLine& cl)
  : command_line(cl),
  ui_task(NULL) {
 }

 const base::CommandLine& command_line;
#if defined(OS_WIN)
 HINSTANCE hInstance;
#endif
 base::Closure* ui_task;
};

}

#endif
