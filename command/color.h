// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMAND_COLOR_H__
#define COMMAND_COLOR_H__

#include "build/build_config.h"
#if defined(OS_WIN)
#include <windows.h>
#endif

namespace command {

enum class BgColor {
 Black = 0,
 Blue = BACKGROUND_BLUE,
 Green = BACKGROUND_GREEN,
 Cyan = (BACKGROUND_BLUE | BACKGROUND_GREEN),
 Red = BACKGROUND_RED,
 Magenta = (BACKGROUND_BLUE | BACKGROUND_RED),
 Yellow = (BACKGROUND_GREEN | BACKGROUND_RED),
 White = (BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED),
};


enum class FgColor {
 Black = 0,
 Blue = FOREGROUND_BLUE,
 Green = FOREGROUND_GREEN,
 Cyan = (FOREGROUND_BLUE | FOREGROUND_GREEN),
 Red = FOREGROUND_RED,
 Magenta = (FOREGROUND_BLUE | FOREGROUND_RED),
 Yellow = (FOREGROUND_GREEN | FOREGROUND_RED),
 White = (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED),
};

}

#endif