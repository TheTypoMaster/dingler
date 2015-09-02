// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KERNEL_NOTIFICATION_OBSERVER_H_
#define KERNEL_NOTIFICATION_OBSERVER_H_

namespace kernel {

class NotificationDetails;
class NotificationSource;

// This is the base class for notification observers. When a matching
// notification is posted to the notification service, Observe is called.
class NotificationObserver {
 public:
  virtual void Observe(int type,
                       const NotificationSource& source,
                       const NotificationDetails& details) = 0;

 protected:
  virtual ~NotificationObserver() {}
};

}  // namespace dingler

#endif  // KERNEL_NOTIFICATION_OBSERVER_H_