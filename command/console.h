// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMAND_CONSOLE_H__
#define COMMAND_CONSOLE_H__

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/ref_counted.h"
#include "base/containers/hash_tables.h"
#include "base/command_line.h"
#include "base/synchronization/waitable_event.h"
#include "base/threading/thread.h"
#include "command/status.h"
#include "command/screen_buffer.h"
#include "command/color.h"
#include "command/size.h"

namespace command {
class CommandThread;
class ScriptHost;
class Screen;
class Session;
class ScreenDriver;

class Console {
public:
 static Console* Instance();

 Console();
 ~Console();

 CommandThread* main_thread() const { return main_thread_.get(); }
 void set_main_thread(CommandThread* thread) { main_thread_.reset(thread); }

 ScriptHost* script_host() const { return script_host_.get(); }

 Screen* current_screen() const;

 Session* session() const { return session_.get(); }

 base::MessageLoop* io_message_loop() { return io_thread_.message_loop(); }

 base::MessageLoop* reader_message_loop() { return reader_thread_.message_loop(); }

 bool Init(const base::CommandLine& cmd, Size initsz);

 void AddRefProcess();
 void ReleaseProcess();

 base::WaitableEvent* GetShutDownEvent();

 Screen* NewScreen();
 Status SetCurrentScreen(int index);
 Screen* GetScreen(int index);
 int AddScreen(Screen* screen);
 void RemoveScreen(int index);
 // copy a region from screen a to b
 bool ClipScreen(int src, int src_left, int src_top, int src_right, int src_bottom,
  int dest, int dest_left, int dest_top, int dest_right, int dest_bottom);

private:

 scoped_ptr<ScriptHost> script_host_;

 scoped_ptr<Session> session_;

 scoped_ptr<ScreenDriver> driver_;

 scoped_ptr<CommandThread> main_thread_;

 base::WaitableEvent shutdown_event_;

 base::Thread io_thread_;

 base::Thread reader_thread_;

 base::hash_map<int, Screen *> screens_;

 int screen_count_;

 int current_screen_;

 int ref_count_;

 DISALLOW_COPY_AND_ASSIGN(Console);
};

}

#endif