// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KERNEL_PROCESS_FINDER_WIN_H_
#define KERNEL_PROCESS_FINDER_WIN_H_

#include <windows.h>
#include "base/time/time.h"

namespace base {
 class FilePath;
}

namespace kernel {
 
enum NotifyShellResult {
 NOTIFY_SUCCESS,
 NOTIFY_FAILED,
 NOTIFY_WINDOW_HUNG,
};

// Finds an already running window if it exists.
HWND FindRunningWindow(const base::FilePath& user_data_dir);

// Attempts to send the current command line to an already running instance of
// Chrome via a WM_COPYDATA message.
// Returns true if a running Chrome is found and successfully notified.
// |fast_start| is true when this is being called on the window fast start path.
NotifyShellResult AttemptToNotifyRunningChrome(HWND remote_window,
 bool fast_start);

// Changes the notification timeout to |new_timeout|, returns the old timeout.
base::TimeDelta SetNotificationTimeoutForTesting(base::TimeDelta new_timeout);

}  // namespace kernel

#endif  // KERNEL_PROCESS_FINDER_WIN_H_
