// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "common/process_type.h"

#include "base/logging.h"

namespace common {

std::string GetProcessTypeName(int type) {

 switch (type) {
 case PROCESS_TYPE_KERNEL:
  return "Kernel";
 case PROCESS_TYPE_CONTAINER:
  return "Container";
 case PROCESS_TYPE_APPLICATION:
  return "Application";
 case PROCESS_TYPE_COMMAND:
  return "Command";
 case PROCESS_TYPE_GPU:
  return "GPU";
 case PROCESS_TYPE_UNKNOWN:
  DCHECK(false) << "Unknown child process type!";
  return "Unknown";
 }

 return "Unknown";
}

} // namespace common
