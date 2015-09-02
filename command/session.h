// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMAND_COMMAND_SESSION_H__
#define COMMAND_COMMAND_SESSION_H__

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"

namespace command {
class Connection;

class Session {
public:
 Session();
 ~Session();

 Connection* connection() const { return conn_.get(); }

 void Start();
 void End();

private:

 scoped_ptr<Connection> conn_;

 bool started_;

 DISALLOW_COPY_AND_ASSIGN(Session);
};

}

#endif