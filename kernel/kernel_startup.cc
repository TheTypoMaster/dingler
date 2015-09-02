// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "kernel/kernel_startup.h"

#include "base/logging.h"

namespace kernel {

// static 
 void KernelStartup::ProcessCommandLineAlreadyRunning(const base::CommandLine& command_line,
    const base::FilePath& current_directory,
    const base::FilePath& startup_container_dir) {
 LOG(INFO) << "KernelStartup::ProcessCommandLineAlreadyRunning called.";
}

KernelStartup::KernelStartup() {

}

KernelStartup::~KernelStartup() {

}

}