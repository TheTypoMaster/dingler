// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DINGLER_IMAGE_OBJECT_H_
#define DINGLER_IMAGE_OBJECT_H_

#include "base/basictypes.h"

namespace image {

class Object {
public:
 
 enum Type {
  DOCUMENT,
  BLOB,
 };
 
 virtual ~Object();

 Type type() const { return type_; }

protected:
 Object(Type type);
private:
 
 Type type_;

 DISALLOW_COPY_AND_ASSIGN(Object);
};

}

#endif