// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMAND_KEY_H__
#define COMMAND_KEY_H__

namespace command {

// ascii keycode table
enum KeyCode {
 kNull = 0,
 kBackspace = 8,
 kTab = 9,
 kShift = 10,
 lCtrl = 17,
 kReturn = 13,
 kCapsLock = 14,
 kEscape = 27,
 kSpace = 32,
 kExcl = 33, // !
 kQuot = 34, // "
 kHash = 35, // #
 kDollar = 36, // $
 
 kLeft = 37,
 kUp = 38,
 kRight = 39,
 kDown = 40,
 kInsert = 45,
 kDelete = 46,
 kNumLock = 90,
 kDel = 127,
};

struct KeyEvent {
 char ch;
 bool printable;
 //int flags;
};

}

#endif