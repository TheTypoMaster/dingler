// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMAND_COMMAND_HISTORY_H__
#define COMMAND_COMMAND_HISTORY_H__

#include "base/basictypes.h"

namespace command {

class CommandHistory {
public:
 CommandHistory();
 ~CommandHistory();
private:

 DISALLOW_COPY_AND_ASSIGN(CommandHistory);
};

}

#endif