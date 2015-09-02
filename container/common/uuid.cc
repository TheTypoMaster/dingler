// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/common/uuid.h"
#include "base/guid.h"

namespace container {

UUID GenerateUUID() {
 return base::GenerateGUID();
}

}