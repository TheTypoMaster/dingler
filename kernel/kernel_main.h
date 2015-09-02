// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KERNEL_MAIN_H__
#define KERNEL_MAIN_H__

namespace common {
struct MainParams;
}

namespace kernel {

int Main(const common::MainParams& params);

}

#endif
