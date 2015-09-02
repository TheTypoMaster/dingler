// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KERNEL_KERNEL_STARTUP_H_
#define KERNEL_KERNEL_STARTUP_H_

#include "base/basictypes.h"
#include "base/files/file_path.h"
#include "base/command_line.h"

namespace kernel {

class KernelStartup {
public:
 
 static void ProcessCommandLineAlreadyRunning(const base::CommandLine& command_line,
    const base::FilePath& current_directory,
    const base::FilePath& startup_container_dir);

 KernelStartup();
 ~KernelStartup();

private:
 DISALLOW_COPY_AND_ASSIGN(KernelStartup);
};

}

#endif
