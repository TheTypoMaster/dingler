// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DINGLER_DB_CURSOR_H_
#define DINGLER_DB_CURSOR_H_

#include "base/basictypes.h"
#include "db/status.h"
#include "db/op.h"
#include "third_party/bt/sqlite3.h"
#include "third_party/bt/sqliteInt.h"
#include "third_party/bt/btree.h"

namespace db {
class Table;
class Cursor {
public:
 Cursor(Table* table, BtCursor* cursor);
 ~Cursor();

 Table* table() const { return table_; }

 bool is_valid() const;

 size_t Count() const;

 Status Seek(SeekOp op);
 // get the payload at the current cursor position
 void GetPayload(const void** payload, size_t* size);

private:

 Table* table_;

 BtCursor* cursor_;

 DISALLOW_COPY_AND_ASSIGN(Cursor);
};

}

#endif