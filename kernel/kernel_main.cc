// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "kernel/kernel_main.h"

#include "common/main_params.h"
#include "kernel/kernel_main_runner.h"

namespace kernel {

int Main(const common::MainParams& params) {
 KernelMainRunner main_runner;

 int exit_code = main_runner.Initialize(params);
 
 if (exit_code >= 0)
  return exit_code;

 exit_code = main_runner.Run();

 main_runner.Shutdown();

 return exit_code;
}

}
