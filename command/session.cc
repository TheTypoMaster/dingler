// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "command/session.h"
#include "command/connection.h"

namespace command {

Session::Session(): started_(false){

}

Session::~Session(){

}

void Session::Start() {
 started_ = true;
}

void Session::End() {
 started_ = false;
}

}