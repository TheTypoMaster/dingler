// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMON_PROCESS_INFO_H__
#define COMMON_PROCESS_INFO_H__

#include <vector>

#include "container/common/uuid.h"

namespace common {

struct ProcessInfo {
 container::UUID id;
};

typedef std::vector<ProcessInfo>::iterator ProcessIterator;

}

#endif