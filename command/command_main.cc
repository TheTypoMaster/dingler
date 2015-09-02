// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "command/command_main.h"

#include "base/command_line.h"
#include "base/message_loop/message_loop.h"
#include "base/run_loop.h"
#include "common/main_params.h"
#include "command/console.h"
#include "command/command_thread.h"

namespace command {

int Main(const common::MainParams& params) {
 scoped_ptr<base::MessageLoop> main_message_loop(new base::MessageLoop());
 base::PlatformThread::SetName("CommandMain");

 // temporary hack
 auto args = params.command_line.GetArgs();
 
 for (auto it = args.begin(); it != args.end(); ++it) {
  if (it->compare(L"console") == 0){
   Console cons;

   if (!cons.Init(params.command_line, Size(80, 60)))
    return 0;

   cons.set_main_thread(new CommandThread(main_message_loop.Pass()));

   base::MessageLoop::current()->Run();
  }
 }

 return 0;
}

}