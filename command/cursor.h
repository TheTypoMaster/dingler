// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMAND_CURSOR_H__
#define COMMAND_CURSOR_H__

namespace command {

enum CursorStyle {
 Underscore,
 Box
};

struct Cursor {
 int x, y;
 Cursor() : x(-1), y(-1) {}
 Cursor(int _x, int _y) : x(_x), y(_y) {}
};

}

#endif