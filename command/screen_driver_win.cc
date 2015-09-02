// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <windows.h>

#include "base/logging.h"
#include "command/screen_driver.h"
#include "command/screen.h"

namespace command {

ScreenDriver::ScreenDriver() {
 
}

ScreenDriver::~ScreenDriver() {

}

InputBuffer ScreenDriver::STDIN() {
 if (stdin_.handle == INVALID_HANDLE_VALUE) {
  auto handle = GetStdHandle(STD_INPUT_HANDLE);
  DCHECK(handle != INVALID_HANDLE_VALUE);
  stdin_.handle = handle;
 }

 return stdin_;
}

OutputBuffer ScreenDriver::STDOUT() {
 if (stdout_.handle == INVALID_HANDLE_VALUE) {
  auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
  DCHECK(handle != INVALID_HANDLE_VALUE);
  stdout_.handle = handle;
 }

 return stdout_;
}

OutputBuffer ScreenDriver::STDERR() {
 if (stderr_.handle == INVALID_HANDLE_VALUE) {
  auto handle = GetStdHandle(STD_ERROR_HANDLE);
  DCHECK(handle != INVALID_HANDLE_VALUE);
  stderr_.handle = handle;
 }

 return stderr_;
}

bool ScreenDriver::Init() {

 /*if (!AttachConsole(GetCurrentProcessId()))
  return false;*/

 return true;
}

void ScreenDriver::Dispose() {
 //FreeConsole();
}


Status ScreenDriver::CreateScreen(OutputBuffer outbuf, Screen** out) {
 *out = new Screen(this, outbuf, STDIN());
 return Status::OK;
}

Status ScreenDriver::CreateOutputBuffer(OutputBuffer* buf) {

 auto handle = CreateConsoleScreenBuffer(
  GENERIC_READ |
  GENERIC_WRITE,
  FILE_SHARE_READ |
  FILE_SHARE_WRITE,
  NULL,
  CONSOLE_TEXTMODE_BUFFER,
  NULL);

 if (handle == INVALID_HANDLE_VALUE)
  return Status::ERR_INVALID_SCREENBUFFER;

 *buf = OutputBuffer(handle);

 return Status::OK;
}

bool ScreenDriver::CopyBuffer(OutputBuffer src, int src_left, int src_top, int src_right, int src_bottom,
 OutputBuffer dest, int dest_left, int dest_top, int dest_right, int dest_bottom) {
 DCHECK(src.handle != INVALID_HANDLE_VALUE && dest.handle != INVALID_HANDLE_VALUE);
 // INPUT_RECORD records;
 // read from src
 //ReadTerminalInput(src.handle, &records, ;
 // write to dest
 //WriteTerminalOutput()
 return false;
}

DisplayMode ScreenDriver::GetDisplayMode() {
 DisplayMode mode(DisplayMode::NONE);
 LPDWORD m = nullptr;
 
 if (!GetConsoleDisplayMode(m))
  return mode;

 if (*m == CONSOLE_FULLSCREEN_MODE) {
  mode = DisplayMode::FULLSCREEN;
 }
 else if (*m == CONSOLE_WINDOWED_MODE) {
  mode = DisplayMode::WINDOWED;
 }

 return mode;
}

Status ScreenDriver::SetDisplayMode(DisplayMode mode) {
 return Status::OK;
}

}