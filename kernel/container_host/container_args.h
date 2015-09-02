// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KERNEL_CONTAINER_CONTAINER_ARGS_H__
#define KERNEL_CONTAINER_CONTAINER_ARGS_H__

namespace kernel {

struct ContainerArgs {
 
};

struct ContainerRunArgs : ContainerArgs {

};

struct ContainerStopArgs : ContainerArgs {

};

struct ContainerStartArgs : ContainerArgs {

};

struct ContainerKillArgs : ContainerArgs {

};

struct ContainerListProcessArgs : ContainerArgs {

};

}

#endif