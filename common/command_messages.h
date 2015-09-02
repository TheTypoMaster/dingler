// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ipc/ipc_message_macros.h"

#undef IPC_MESSAGE_EXPORT
#define IPC_MESSAGE_EXPORT// CONTENT_EXPORT

#define IPC_MESSAGE_START CommandMsgStart


// Messages sent from the kernel to the console process.
IPC_MESSAGE_CONTROL0(CommandMsg_Hello)

// Messages sent from the console to the kernel.
IPC_MESSAGE_CONTROL0(CommandHostMsg_HelloReply)