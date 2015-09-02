// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BIN_DINGLER_MAIN_RUNNER_H__
#define BIN_DINGLER_MAIN_RUNNER_H__

#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "bin/dingler/dingler_main.h"
#include "common/main_params.h"
#include "common/process_type.h"
#include "common/client.h"

namespace base {
class AtExitManager;
}

namespace kernel {
class KernelClient;
}

namespace container {
class ContainerClient;
}

namespace application {
class ApplicationClient;
}

namespace dingler {
class ClientInitializer;

class MainRunner {
public:
 MainRunner();
 ~MainRunner();

 int Initialize(const MainParams& params);
 int Run();
 void Shutdown();

private:
 friend class ClientInitializer;

 kernel::KernelClient* CreateKernelClient();
 /*container::ContainerClient* CreateContainerClient();
 application::ApplicationClient* CreateApplicationClient();
*/
#if defined(USE_TCMALLOC)
 static bool GetAllocatorWasteSizeThunk(size_t* size);
 static void GetStatsThunk(char* buffer, int buffer_length);
 static void ReleaseFreeMemoryThunk();
#endif

 int RunProcess(common::ProcessType type,
  const common::MainParams& main_params);

 scoped_ptr<base::AtExitManager> exit_manager_;

 // True if the runner has been initialized.
 bool is_initialized_;
 // True if the runner has been shut down.
 bool is_shutdown_;

 common::Client client_;

#if defined(OS_WIN)
 HINSTANCE hinstance_;
#endif

 DISALLOW_COPY_AND_ASSIGN(MainRunner);
};

}

#endif