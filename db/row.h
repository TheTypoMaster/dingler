// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DINGLER_DB_ROW_H_
#define DINGLER_DB_ROW_H_

#include "base/basictypes.h"
#include "db/globals.h"

namespace db {
class Schema;

class Row {
public:
 Row(rowid_t rowid, const Schema& schema);
 ~Row();

 bool dirty() const { return dirty_; }
 void set_dirty(bool dirty) { dirty_ = dirty; }

private:
 
 const Schema& schema_;

 rowid_t rowid_;

 bool    dirty_;

 DISALLOW_COPY_AND_ASSIGN(Row);
};


}

#endif