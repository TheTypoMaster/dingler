// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KERNEL_CONTAINER_CONTAINER_STATE_H__
#define KERNEL_CONTAINER_CONTAINER_STATE_H__

namespace kernel {

enum class ContainerState {
 ZERO,
 LOADING,
 LOADED,
 UNLOADED,
 STARTING,
 STARTED,
 STOPPING,
 STOPPED,
 EXITING
};

}

#endif