// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <algorithm>

#include "db/table.h"

#include "db/cursor.h"
#include "db/index.h"
#include "db/mutator.h"
#include "db/row.h"
#include "third_party/bt/sqlite3.h"
#include "third_party/bt/sqliteInt.h"
#include "third_party/bt/btree.h"
#include "third_party/bt/btreeInt.h"

namespace db {

Table::Table(Context* context, 
  tableid_t id,
  std::string name, 
  Schema schema):
   context_(context),
   schema_(std::move(schema)), 
   id_(id),
   name_(std::move(name)){

}

Table::~Table() {

}

rowid_t Table::GetLastRowID() const {
 return -1;
}

Index* Table::GetPrimaryKeyIndex() const {
 return nullptr;
}

scoped_ptr<Cursor> Table::CreateCursor() {
 auto bt_cursor = new BtCursor;
 sqlite3BtreeCursorZero(bt_cursor);
 return scoped_ptr<Cursor>(new Cursor(this, bt_cursor)).Pass();
}

Row* Table::NewRow() {
 auto rowid = GetLastRowID();
 return new Row(rowid, schema());
}

}