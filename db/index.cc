// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "db/index.h"

namespace db {

Index::Index(Table* table, Type type, const std::string& name) :
 table_(table), name_(name), column_count_(0), type_(type) {

}
 
Index::~Index() {

}

}