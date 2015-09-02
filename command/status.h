// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMAND_STATUS_H__
#define COMMAND_STATUS_H__

namespace command {

enum class Status {
 OK,
 ERR,
 ERR_INVALID_SCREENBUFFER,
 ERR_SETMODE_FAILED,
 ERR_OUT_OF_RANGE,
};

}

#endif