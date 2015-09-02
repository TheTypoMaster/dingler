// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMAND_SCREEN_DRIVER_H__
#define COMMAND_SCREEN_DRIVER_H__

#include "base/basictypes.h"
#include "command/status.h"
#include "command/screen_buffer.h"

namespace command {
class Screen;

enum class DisplayMode {
 NONE,
 WINDOWED,
 FULLSCREEN
};

class ScreenDriver {
public:
 ScreenDriver();
 ~ScreenDriver();

 InputBuffer STDIN();
 OutputBuffer STDOUT();
 OutputBuffer STDERR();

 bool Init();
 void Dispose();

 Status CreateScreen(OutputBuffer outbuf, Screen** out);
 Status CreateOutputBuffer(OutputBuffer* buf);
 
 DisplayMode GetDisplayMode();
 Status SetDisplayMode(DisplayMode mode);

 // copy a rect from a to b
 bool CopyBuffer(OutputBuffer src, int src_left, int src_top, int src_right, int src_bottom,
  OutputBuffer dest, int dest_left, int dest_top, int dest_right, int dest_bottom);

private:
 
 InputBuffer stdin_;
 OutputBuffer stdout_;
 OutputBuffer stderr_;

 DISALLOW_COPY_AND_ASSIGN(ScreenDriver);
};

}

#endif