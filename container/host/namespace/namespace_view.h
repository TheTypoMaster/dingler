// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_VIEW_H__
#define CONTAINER_HOST_NAMESPACE_VIEW_H__

#include "base/basictypes.h"

namespace container {
 /*
  * Each namespace can have one or more views
  * The views can be accessed by url:
  *
  * $ me:proc/all
  *
  * which is sugar for
  *
  * $ from('me:proc/all').select()
  *
  */
class NamespaceView {
public:
 NamespaceView();
 ~NamespaceView();
private:


 DISALLOW_COPY_AND_ASSIGN(NamespaceView);
};

}

#endif