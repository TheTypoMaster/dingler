// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_IO_SIGNAL_H__
#define CONTAINER_HOST_NAMESPACE_IO_SIGNAL_H__

namespace container {

enum class IOSignalCode {
 // app sockets
 KILL
};
// signals are events sent to the io resources
// so they can act through a common umbrela
struct IOSignal {

};

}

#endif