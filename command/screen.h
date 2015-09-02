// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMAND_SCREEN_H__
#define COMMAND_SCREEN_H__

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/containers/hash_tables.h"
#include "base/memory/scoped_vector.h"
#include "command/screen_buffer.h"
#include "command/status.h"
#include "command/color.h"
#include "command/cursor.h"
#include "command/key.h"

namespace command {
class ScreenDriver;
// immediate = command line mode
// deferred = editor (multi-line) mode
class ImmediateRenderer;
class DeferredRenderer;

class Screen {
public:

 class ScreenData {
 public:
  ScreenData();
  ~ScreenData();

  void Init(int rows, int cols);
  
  int col_count() const { return col_count_; }
  
  int row_count() const { return row_count_; }

  int row() const { return row_; }
  int col() const { return col_; }

  //void SetCurrentRow(int row);
  char* GetRowData(int row, int col, size_t* len);
  void SetRowData(int row, int col, const char* data, size_t len);
  void ClearRow(int row);

 private:
  
  void* buffer_;
  int buflen_;
  
  //index of current row
  int row_;
  //index of current row
  int col_;
  // pointer of current row
  char* curr_;

  int row_count_;
  int col_count_;

  DISALLOW_COPY_AND_ASSIGN(ScreenData);
 };

 class Renderer {
 public:
  virtual ~Renderer(){}
  virtual void PutChar(char c) = 0;
  virtual void PutCharAt(char c, int x, int y) = 0;
  virtual void PutString(const std::string& text) = 0;
  virtual void PutString(const char* text, size_t len) = 0;
  virtual void PutStringAt(const std::string& text, int x, int y) = 0;
  virtual void PutStringAt(const char* text, size_t len, int x, int y) = 0;
  virtual void ClearChar() = 0;
  virtual void NewLine() = 0;
  virtual void Clear(BgColor color) = 0;
  virtual void Render() = 0;
 };

 Screen(ScreenDriver* driver,
   OutputBuffer outbuf, 
   InputBuffer input);

 ~Screen();

 ScreenDriver* driver() const { return driver_; }

 OutputBuffer buffer() const { return output_; }

 bool immediate_mode() const { return immediate_mode_; }

 bool Init(bool immediate_mode, bool show_prompt);

 void ShowPrompt(bool prompt) { show_prompt_ = prompt; }

 void SetPromptSign(const char* prompt_sign) { prompt_sign_ = prompt_sign; }

 Status GetOutputBufferSize(int* w, int* h);
 Status SetOutputBufferSize(int w, int h);

 void GetScreenSize(int* w, int* h) const;
 Status SetScreenSize(int w, int h);

 BgColor GetBackgroundColor();
 void SetBackgroundColor(BgColor color);

 FgColor GetForegroundColor();
 void SetForegroundColor(FgColor color);

 bool ReadKey(KeyEvent* kev);
 int ReadLine(char** str);

 void PutChar(char c);
 void PutCharAt(char c, int x, int y);
 void ClearChar();
 void PutString(const std::string& str);
 void PutString(const char* text, size_t len);
 void PutStringAt(const std::string& text, int x, int y);
 void PutStringAt(const char* text, size_t len, int x, int y);
 void NewLine();
 
 // cursor
 Cursor GetCursor();
 bool SetCursor(Cursor cursor);
 bool SetCursor(int x, int y);
 void SetCursorStyle(CursorStyle style);
 void SetCursorVisibility(bool visible);

 void Clear(BgColor color);
 void Render();

private:
 friend class ImmediateRenderer;
 friend class DeferredRenderer;

 int Print(char ch, bool advance);
 int Print(const char* str, size_t len);
 int Print(int x, int y, char ch, bool advance);
 int Print(int x, int y, const char* str, size_t len);

 // TODO: move those to Driver so screen can be portable and reusable
 int Print(OutputBuffer buf, int x, int y, const char* str, size_t len);
 int Print(OutputBuffer buf, int x, int y, char ch, bool advance);
 int Print(OutputBuffer buf, const ScreenData& data);

 void Clear(OutputBuffer buf, BgColor color);

 // TODO: move those to Driver so screen can be portable and reusable
 PINPUT_RECORD NextEvent(bool advance, bool wait);

 // TODO: move those to Driver so screen can be portable and reusable
 bool ProcessKey(KEY_EVENT_RECORD k_event, KeyEvent* kev);
 
 ScreenDriver* driver_;

 scoped_ptr<Renderer> renderer_;

 OutputBuffer output_;

 InputBuffer input_;

 BgColor bgcolor_;

 FgColor fgcolor_;

 // color attributes cache for windows
 uint16_t color_attr_;

 Cursor cursor_;
 CursorStyle cursor_style_;
 
 int16_t wx_;
 int16_t wy_;
 int16_t wbottom_;
 int16_t wleft_;
 int16_t wright_;
 int16_t wtop_;

 const char* prompt_sign_;

 bool show_prompt_;
 bool immediate_mode_;

 PINPUT_RECORD	event_buffer_;
 // number of events readed
 DWORD nevents_;

 DISALLOW_COPY_AND_ASSIGN(Screen);
};

}

#endif