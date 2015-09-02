// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMAND_SIZE_H__
#define COMMAND_SIZE_H__

namespace command {

struct Size {
 int width;
 int height;

 Size() : width(0), height(0) {}
 Size(int w, int h) : width(w), height(h) {}
};

}

#endif