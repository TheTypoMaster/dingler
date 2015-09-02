// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "bin/dingler/dingler_main.h"
#include "bin/dingler/dingler_main_runner.h"

namespace dingler {

int Main(const MainParams& params) {
 MainRunner main_runner;

 int exit_code = main_runner.Initialize(params);
 if (exit_code > 0)
  return exit_code;

 exit_code = main_runner.Run();

 main_runner.Shutdown();

 return exit_code;
}

}