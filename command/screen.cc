// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <windows.h>

#include "command/screen.h"
#include "base/logging.h"
#include "command/screen_driver.h"

namespace command {

namespace {
 const char kDEFAULT_PROMPT_SIGN[] = "> ";
 const int kDefaultPromptLen = sizeof(kDEFAULT_PROMPT_SIGN);
 const int kMaxEvents = 32;
 const int kDefaultCols = 120; // minha config
 const int kDefaultRows = 40;
}

Screen::ScreenData::ScreenData() :
 buffer_(nullptr),
 buflen_(0),
 row_(0),
 col_(0),
 curr_(nullptr),
 row_count_(0),
 col_count_(0) {

}

Screen::ScreenData::~ScreenData() {
 if(buflen_ > 0)
  free(buffer_);
}

void Screen::ScreenData::Init(int rows, int cols) {
 buflen_ = sizeof(char) * (rows * cols);
 buffer_ = memset(malloc(buflen_), 0, buflen_);
}

//void Screen::ScreenData::SetCurrentRow(int row) {
// if (row <= row_count_) {
//  // update index
//  row_ = row;
//  // update pointer (todo: this does nothing)
//  curr_ = (char *)buffer_;
// }
//}

char* Screen::ScreenData::GetRowData(int row, int col, size_t* len) {
 // not working
 return (char *)buffer_;
}

void Screen::ScreenData::SetRowData(int row, int col, const char* data, size_t len) {
 // not working
}

void Screen::ScreenData::ClearRow(int row) {
 // not working
}

// Immediate Renderer 

class ImmediateRenderer : public Screen::Renderer {
public:
 ImmediateRenderer(Screen* screen): screen_(screen){ 
  // TODO: GET NUMBER OF ROWS, COLS FROM WINDOWS
  //data_.Init(kDefaultCols, kDefaultRows);
  Prompt();
 }

 ~ImmediateRenderer() override {}

 void PutChar(char c) override {
  // update row data
  //data_.SetRowData(data_.row(), data_.col(), &c, 1);
  // render
  screen_->Print(c, true);
 }
 void PutCharAt(char c, int x, int y) override {
  // update row data
  //data_.SetRowData(data_.row(), data_.col(), &c, 1);
  // render
  screen_->Print(x, y, c, true);
 }

 void PutString(const std::string& text) override {
  //data_.SetRowData(data_.row(), data_.col(), text.c_str(), text.length());
  screen_->Print(text.c_str(), text.length());
 }

 void PutString(const char* text, size_t len) override {
  //data_.SetRowData(data_.row(), data_.col(), text, len);
  screen_->Print(text, len);
 }

 void PutStringAt(const std::string& text, int x, int y) override {
  //data_.SetRowData(x, y, text.c_str(), text.length());
  screen_->Print(x, y, text.c_str(), text.length());
 }

 void PutStringAt(const char* text, size_t len, int x, int y) override {
  //data_.SetRowData(x, y, text, len);
  screen_->Print(x, y, text, len);
 }

 void ClearChar() override {
  screen_->Print(0, false);
 }

 void NewLine() override {
  auto c = screen_->GetCursor();
  screen_->SetCursor(0, c.y + 1);
  Prompt();
 }

 void Clear(BgColor color) override {

 }
 // do nothing in immediate mode
 void Render() override {}

private:
 
 void Prompt() {
  if (screen_->show_prompt_) {
   screen_->Print(kDEFAULT_PROMPT_SIGN, kDefaultPromptLen - 1);
  }
 }

 Screen* screen_;

 //Screen::ScreenData data_;

 DISALLOW_COPY_AND_ASSIGN(ImmediateRenderer);
};

// Deferred Renderer

class DeferredRenderer : public Screen::Renderer {
public:
 
 DeferredRenderer(Screen* screen) : screen_(screen), dirty_(false){
  // TODO: GET NUMBER OF ROWS, COLS FROM WINDOWS
  //data_.Init(kDefaultCols, kDefaultRows);
 }

 ~DeferredRenderer() override {}

 void PutChar(char c) override {
  dirty_ = true;
 }
 void PutCharAt(char c, int x, int y) override {
  dirty_ = true;
 }
 void PutString(const std::string& text) override {
  dirty_ = true;
 }
 void PutString(const char* text, size_t len) override {
  dirty_ = true;
 }
 void PutStringAt(const std::string& text, int x, int y) override {
  dirty_ = true;
 }
 void PutStringAt(const char* text, size_t len, int x, int y) override {
  dirty_ = true;
 }

 void ClearChar() override {
  dirty_ = true;
 }

 void NewLine() override {
  dirty_ = true;
 }

 void Clear(BgColor color) override {
  dirty_ = true;
 }

 void Render() override {
  // render lines
  screen_->Print(screen_->output_, data_);
  dirty_ = false;
 }

private:
 Screen* screen_;

 Screen::ScreenData data_;

 bool dirty_;

 DISALLOW_COPY_AND_ASSIGN(DeferredRenderer);
};

Screen::Screen(ScreenDriver* driver, OutputBuffer outbuf,
 InputBuffer input) : driver_(driver),
 output_(outbuf),
 input_(input),
 cursor_style_(CursorStyle::Box),
 prompt_sign_(kDEFAULT_PROMPT_SIGN),
 immediate_mode_(false),
 event_buffer_(nullptr),
 nevents_(0),
 show_prompt_(false){
  
}

Screen::~Screen() {
 free(event_buffer_);
}


bool Screen::Init(bool immediate_mode, bool show_prompt) {
 CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
 
 show_prompt_ = show_prompt;

 if (!GetConsoleScreenBufferInfo(output_.handle, &csbiInfo))
  return false;

 color_attr_ = csbiInfo.wAttributes;
 cursor_.x = csbiInfo.dwCursorPosition.X;
 cursor_.y = csbiInfo.dwCursorPosition.Y;
 wx_ = csbiInfo.dwSize.X;
 wy_ = csbiInfo.dwSize.Y;
 wbottom_ = csbiInfo.srWindow.Bottom;
 wleft_ = csbiInfo.srWindow.Left;
 wright_ = csbiInfo.srWindow.Right;
 wtop_ = csbiInfo.srWindow.Top;

 SetConsoleMode(input_.handle, 0);

 SetBackgroundColor(BgColor::Magenta);
 SetForegroundColor(FgColor::White);
 
 event_buffer_ = (PINPUT_RECORD) malloc(kMaxEvents * sizeof(INPUT_RECORD));

 immediate_mode_ = immediate_mode;
 if (immediate_mode_){
  renderer_.reset(new ImmediateRenderer(this));
 }
 else {
  renderer_.reset(new DeferredRenderer(this));
 }
 
 return true;
}

void Screen::GetScreenSize(int* w, int* h) const {
 /*COMMAND_SCREEN_BUFFER_INFO csbiInfo;
 if (!GetTerminalScreenBufferInfo(output_.handle, &csbiInfo)) {
  *w = -1;
  *h = -1;
  return;
 }*/

 *w = wright_;
 *h = wbottom_;
}

Status Screen::SetScreenSize(int w, int h) {
 return Status::OK;
}

BgColor Screen::GetBackgroundColor() {
 return bgcolor_;
}

void Screen::SetBackgroundColor(BgColor color) {
 SetConsoleTextAttribute(output_.handle, (int)color);
 bgcolor_ = color;
}

FgColor Screen::GetForegroundColor() {
 return fgcolor_;
}

void Screen::SetForegroundColor(FgColor color) {
 SetConsoleTextAttribute(output_.handle, (int)color);
 fgcolor_ = color;
}

bool Screen::ReadKey(KeyEvent* kev) {
 bool done = false;
 bool is_key = false;

 do {
  //auto ev = NextEvent(false, false);
  auto ev = NextEvent(true, true);

  if (ev) {

   switch (ev->EventType) {
   case KEY_EVENT:
    if (ProcessKey(ev->Event.KeyEvent, kev)) {
     is_key = true;
     done = true;
    }
    break;
   case MOUSE_EVENT:
    done = true;
    break;
   case WINDOW_BUFFER_SIZE_EVENT:
    done = true;
    break;
   case MENU_EVENT:
   case FOCUS_EVENT:
    done = true;
    break;
   default:
    break;
   }

   if (!done) {
    NextEvent(true, false);
   }

  }
  else {
   done = true;
  }

 } while (!done);

 return is_key;
}

int Screen::ReadLine(char** str) {
 char buf[4096];
 int len = 0;
 int pos = 0;
 int padding = show_prompt_ ? kDefaultPromptLen - 1 : 0;
 bool done = false;

 do {
  KeyEvent ev;
  if (ReadKey(&ev)) {
   char ch = ev.ch;
   switch (ch) {
   case kUp: // TODO: handle
    // HistoryBack();
    break;
   case kDown: // TODO: handle
    // HistoryForward();
    break;
   case kLeft: {
    int x = cursor_.x - 1;
    if (x >= padding) {
     SetCursor(x, cursor_.y);
    }
    break;
   }
   case kRight: {
    int x = cursor_.x + 1;
    if (x <= len)
     SetCursor(x, cursor_.y);
    break;
   }
   case kBackspace: {
    int x = cursor_.x - 1;
    if (x >= padding) {
     SetCursor(x, cursor_.y);
     ClearChar();
     len--;
    }
    break;
   }
   case kReturn:
    done = true;
    break;
   case kShift:
   default: // char case
    if (len == 4096) { // tmp buff full
     done = true; // break loop
     break;
    }
    PutChar(ch);
    buf[len] = ch;
    len++;
    break;
   }
   ++pos;
  }
 } while (!done);

 if (len > 0) {
  buf[len] = '\0';
  *str = static_cast<char *>(malloc(len + 1));
  memcpy(*str, buf, len + 1);
 }

 return len;
}

void Screen::PutChar(char c) {
 renderer_->PutChar(c);
}

void Screen::PutCharAt(char c, int x, int y) {
 renderer_->PutCharAt(c, x, y);
}

void Screen::ClearChar() {
 renderer_->ClearChar();
}

void Screen::PutString(const std::string& str) {
 renderer_->PutString(str);
}

void Screen::PutString(const char* text, size_t len) {
 renderer_->PutString(text, len);
}

void Screen::PutStringAt(const std::string& text, int x, int y) {
 renderer_->PutStringAt(text, x, y);
}

void Screen::PutStringAt(const char* text, size_t len, int x, int y) {
 renderer_->PutStringAt(text, len , x, y);
}

void Screen::NewLine() {
 renderer_->NewLine();
}

Cursor Screen::GetCursor() {
 return Cursor(cursor_.x, cursor_.y);
}

bool Screen::SetCursor(Cursor cursor) {
 COORD xy;

 cursor_.x = xy.X = cursor.x;
 cursor_.y = xy.Y = cursor.y;

 if (SetConsoleCursorPosition(output_.handle, xy))
  return true;

 return false;
}

bool Screen::SetCursor(int x, int y) {
 COORD xy;

 cursor_.x = xy.X = x;
 cursor_.y = xy.Y = y;

 if (SetConsoleCursorPosition(output_.handle, xy))
  return true;

 return false;
}

void Screen::SetCursorStyle(CursorStyle style) {
 cursor_style_ = style;
 CONSOLE_CURSOR_INFO CursorInfo;

 CursorInfo.bVisible = TRUE;

 if (style == CursorStyle::Underscore) {
  CursorInfo.dwSize = 25;
 } else if (style == CursorStyle::Box) {
  CursorInfo.dwSize = 100; 
 }

 SetConsoleCursorInfo(output_.handle,
  &CursorInfo);
}

void Screen::SetCursorVisibility(bool visible) {
 CONSOLE_CURSOR_INFO CursorInfo;

 CursorInfo.bVisible = visible ? TRUE: FALSE;

 if (cursor_style_ == CursorStyle::Underscore)
  CursorInfo.dwSize = 25;
 if (cursor_style_ == CursorStyle::Box)
  CursorInfo.dwSize = 100;


 SetConsoleCursorInfo(output_.handle,
  &CursorInfo);
}

Status Screen::GetOutputBufferSize(int* w, int* h) {
 return Status::OK;
}

Status Screen::SetOutputBufferSize(int w, int h) {
 return Status::OK;
}

void Screen::Clear(BgColor color) {
 renderer_->Clear(color);
}

int Screen::Print(char ch, bool advance) {
 return Print(output_, cursor_.x, cursor_.y, ch, advance);
}

int Screen::Print(const char* str, size_t len) {
 return Print(output_, cursor_.x, cursor_.y, str, len);
}

int Screen::Print(int x, int y, char ch, bool advance) {
 return Print(output_, x, y, ch, advance);
}

int Screen::Print(int x, int y, const char* str, size_t len) {
 return Print(output_, x, y, str, len);
}

int Screen::Print(OutputBuffer buf, int x, int y, const char* data, size_t len) {
 COORD xy;
 DWORD written;

 xy.X = cursor_.x = x;
 xy.Y = cursor_.y = y;

 SetCursorVisibility(false);

 if (!WriteConsoleOutputCharacter(buf.handle, data, static_cast<DWORD>(len), xy, &written)) {
  return -1;
 }

 SetCursorVisibility(true);

 cursor_.x += static_cast<int>(len);
 SetCursor(cursor_);

 return static_cast<int>(written);
}

int Screen::Print(OutputBuffer buf, int x, int y, char ch, bool advance) {
 COORD xy;
 DWORD written;

 xy.X = cursor_.x = x;
 xy.Y = cursor_.y = y;

 SetCursorVisibility(false);

 if (!WriteConsoleOutputCharacter(buf.handle, &ch, 1, xy, &written)) {
  return -1;
 }

 SetCursorVisibility(true);
 
 if (advance) {
  ++cursor_.x;
  SetCursor(cursor_);
 }

 return static_cast<int>(written);
}

int Screen::Print(OutputBuffer buf, const ScreenData& data) {
 // TODO: process screen data
 SetCursorVisibility(false);
/*
 if (!WriteTerminalOutput(buf.handle,
  ScreenData->ScreenBuffer,
  Size,
  Position,
  &Rectangle))
  return -1;*/
 SetCursorVisibility(true);

 return 0;
}

bool Screen::ProcessKey(KEY_EVENT_RECORD k_event, KeyEvent* kev) {
 if (k_event.bKeyDown) {
  if (!k_event.uChar.AsciiChar && k_event.wVirtualKeyCode) {   // CTRL)
   kev->ch = (char)k_event.wVirtualKeyCode;
  }
  else {
   kev->ch = k_event.uChar.AsciiChar;
  }
  return true;
 }

 return false;
}

void Screen::Render() {
 renderer_->Render();
}

PINPUT_RECORD Screen::NextEvent(bool advance, bool wait) {
 PINPUT_RECORD ev;
 DWORD nevents;
 int index = 0;
 int ok;

 ok = PeekConsoleInput(input_.handle,
  event_buffer_,
  kMaxEvents,
  &nevents);

 if (!ok || (nevents == 0 && !wait)) {
  return nullptr;
 }

 ok = ReadConsoleInput(input_.handle,
  event_buffer_,
  kMaxEvents,
  &nevents_);

 if (!ok) {
  nevents_ = 0;
 }

 ev = event_buffer_ + index;

 if (advance) {
  if (nevents_ > 0){
   switch (ev->EventType) {
   case KEY_EVENT:
   case MOUSE_EVENT:
   case WINDOW_BUFFER_SIZE_EVENT:
   case MENU_EVENT:
   case FOCUS_EVENT:
    ++index;
    break;
   default:
    ++index;
    break;
   }
   // consume event
   --nevents_;
  }
 }

 return ev;
}

//void Screen::ProcessFocusEvent(FOCUS_EVENT_RECORD f_event) {
//
//}
//
//void Screen::ProcessMouseEvent(MOUSE_EVENT_RECORD mo_event) {
//
//}
//
//void Screen::ProcessMenuEvent(MENU_EVENT_RECORD me_event) {
//
//}
//
//void Screen::ProcessWindowEvent(WINDOW_BUFFER_SIZE_RECORD w_event) {
//
//}

}