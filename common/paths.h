// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMON_PATHS_H_
#define COMMON_PATHS_H_

#include "build/build_config.h"

namespace base {
class FilePath;
}

namespace common {

enum {
  PATH_START = 1000,
  CHILD_PROCESS_EXE = PATH_START,
  DIR_APP,         // Directory where dlls and data reside.
  DIR_LOGS,        // Directory where logs should be written.
  DIR_ROOT,    		// Dingler Root Directory
  DIR_RESOURCES,   // Directory containing separate file resources
  PATH_END
};


bool GetDefaultRootDirectory(base::FilePath* result);

// Call once to register the provider for the path keys defined above.
void RegisterPathProvider();

}

#endif
