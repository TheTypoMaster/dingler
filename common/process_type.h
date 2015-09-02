// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMON_PROCESS_TYPE_H__
#define COMMON_PROCESS_TYPE_H__

#include <string>

namespace common {

enum ProcessType {
 PROCESS_TYPE_UNKNOWN = 1,
 PROCESS_TYPE_KERNEL,
 PROCESS_TYPE_COMMAND,
 PROCESS_TYPE_GPU,
 PROCESS_TYPE_CONTAINER,
 PROCESS_TYPE_APPLICATION,
 PROCESS_TYPE_END,
 PROCESS_TYPE_MAX = PROCESS_TYPE_END,
};

std::string GetProcessTypeName(int type);

}

#endif