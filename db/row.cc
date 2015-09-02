// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "db/row.h"

namespace db {

Row::Row(rowid_t rowid, const Schema& schema) : schema_(schema), 
 dirty_(false){

}

Row::~Row() {

}

}