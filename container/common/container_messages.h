// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ipc/ipc_message_macros.h"
#include "base/files/file_path.h"

#define IPC_MESSAGE_START ContainerMsgStart
#undef IPC_MESSAGE_EXPORT
#define IPC_MESSAGE_EXPORT

// Messages sent from the console/app to the container

// Ask the host to mount the given volume
IPC_MESSAGE_CONTROL2(ContainerHost_Mount,
                     std::string, /* volume*/
                     std::string /* point*/)

 // Ask the host to umount the given volume
 IPC_MESSAGE_CONTROL1(ContainerHost_Umount,
                      std::string /* point*/)

 // messages sent from the container to