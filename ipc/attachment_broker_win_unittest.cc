// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "build/build_config.h"

#include <windows.h>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/process/process.h"
#include "ipc/attachment_broker_messages.h"
#include "ipc/attachment_broker_win.h"
#include "ipc/handle_attachment_win.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace IPC {

TEST(AttachmentBrokerWinTest, ReceiveValidMessage) {
  HANDLE handle = LongToHandle(8);
  base::ProcessId destination = base::Process::Current().Pid();
  scoped_refptr<internal::HandleAttachmentWin> attachment(
      new internal::HandleAttachmentWin(handle));
  AttachmentBrokerMsg_WinHandleHasBeenDuplicated msg(
      attachment->GetWireFormat(destination));
  AttachmentBrokerWin attachment_broker;
  EXPECT_TRUE(attachment_broker.OnMessageReceived(msg));
  EXPECT_EQ(1u, attachment_broker.attachments_.size());

  scoped_refptr<BrokerableAttachment> received_attachment =
      attachment_broker.attachments_.front();
  EXPECT_EQ(BrokerableAttachment::WIN_HANDLE,
            received_attachment->GetBrokerableType());
  internal::HandleAttachmentWin* received_handle_attachment =
      static_cast<internal::HandleAttachmentWin*>(received_attachment.get());
  EXPECT_EQ(handle, received_handle_attachment->get_handle());
}

TEST(AttachmentBrokerWinTest, ReceiveInvalidMessage) {
  HANDLE handle = LongToHandle(8);
  base::ProcessId destination = base::Process::Current().Pid() + 1;
  scoped_refptr<internal::HandleAttachmentWin> attachment(
      new internal::HandleAttachmentWin(handle));
  AttachmentBrokerMsg_WinHandleHasBeenDuplicated msg(
      attachment->GetWireFormat(destination));
  AttachmentBrokerWin attachment_broker;
  EXPECT_TRUE(attachment_broker.OnMessageReceived(msg));
  EXPECT_EQ(0u, attachment_broker.attachments_.size());
}

}  // namespace IPC
