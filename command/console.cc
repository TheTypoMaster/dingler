// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "command/console.h"

#include "base/run_loop.h"
#include "base/lazy_instance.h"
#include "base/threading/thread.h"
#include "base/threading/thread_local.h"
#include "build/build_config.h"
#include "command/script_host.h"
#include "command/command_executor.h"
#include "command/screen_driver.h"
#include "command/screen.h"
#include "command/session.h"
#include "command/command_thread.h"

namespace command {

namespace {
 
 base::LazyInstance<base::ThreadLocalPointer<Console> > g_lazy_tls =
  LAZY_INSTANCE_INITIALIZER;
 
} // namespace

// static 
Console* Console::Instance() {
 return g_lazy_tls.Pointer()->Get();
}

Console::Console():
  driver_(new ScreenDriver()),
  ref_count_(0),
  shutdown_event_(true, false),
  io_thread_("Dingler_ConsoleIOThread"),
  reader_thread_("Dingler_ConsoleReaderThread"),
  screen_count_(0),
  current_screen_(-1){
 g_lazy_tls.Pointer()->Set(this);
 CHECK(io_thread_.StartWithOptions(
  base::Thread::Options(base::MessageLoop::TYPE_IO, 0)));
 CHECK(reader_thread_.StartWithOptions(
  base::Thread::Options(base::MessageLoop::TYPE_IO, 0)));
}

Console::~Console() {
 shutdown_event_.Signal();

 driver_->Dispose();
 
 if (main_thread_) {
  main_thread_->Shutdown();
 }

 g_lazy_tls.Pointer()->Set(NULL);
 io_thread_.Stop();
 reader_thread_.Stop();

 for (auto it = screens_.begin(); it != screens_.end(); ++it) {
  auto screen = it->second;
  delete(screen);
 }

}

Screen* Console::current_screen() const { 
 return screens_.at(current_screen_);
}

bool Console::Init(const base::CommandLine& cmd, Size initsz) {
 Screen* screen;

 session_.reset(new Session());

 if (!driver_->Init())
  return false;

 driver_->CreateScreen(driver_->STDOUT(), &screen);
 
 int index = AddScreen(screen);
 SetCurrentScreen(index);

 screen->Init(true, true);
 
 return true;
}

base::WaitableEvent* Console::GetShutDownEvent() {
 return &shutdown_event_;
}

void Console::AddRefProcess() {
 ref_count_++;
}

void Console::ReleaseProcess() {
 DCHECK(ref_count_);
 if (--ref_count_)
  return;

 main_thread_->OnProcessFinalRelease();
}


Screen* Console::NewScreen() {
 OutputBuffer buf;
 Screen* out;
 
 driver_->CreateOutputBuffer(&buf);
 
 if (driver_->CreateScreen(buf, &out) != Status::OK)
  return nullptr;

 return out;
}

Status Console::SetCurrentScreen(int index) {
 Screen* ns = GetScreen(index);
 if (!ns) {
  return Status::ERR_OUT_OF_RANGE;
 }
 if (current_screen_ != -1) {
  Screen* current = current_screen();
  if (current->buffer().handle != ns->buffer().handle) { // does this work as expected?
   SetConsoleActiveScreenBuffer(ns->buffer().handle);
   current_screen_ = index;
  }
 } else { // probably the first time
  SetConsoleActiveScreenBuffer(ns->buffer().handle);
  current_screen_ = index;
 }

 return Status::OK;
}

Screen* Console::GetScreen(int index) {
 return screens_.at(index);
}

int Console::AddScreen(Screen* screen) {
 int idx = screen_count_;
 screens_[idx] = screen;
 ++screen_count_;
 return idx;
}

void Console::RemoveScreen(int index) {
 auto i = screens_.erase(index);
 if (i > 0)
  --screen_count_;
}

bool Console::ClipScreen(int src, int src_left, int src_top, int src_right, int src_bottom,
 int dest, int dest_left, int dest_top, int dest_right, int dest_bottom) {
 return false;
}

}