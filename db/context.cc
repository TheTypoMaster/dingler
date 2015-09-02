// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "db/context.h"

#include "base/logging.h"
#include "db/schema.h"
#include "db/table.h"
#include "db/index.h"
#include "db/transaction.h"

namespace db {

 /*
 BtCursor* cursor;

  sqlite3BtreeEnter(db_);

  int rc = sqlite3BtreeBeginTrans(db_, 1);

  if (rc == SQLITE_OK){
   int pgno;
   rc = sqlite3BtreeCreateTable(db_, &pgno, BTREE_INTKEY);
   if (rc == SQLITE_OK){
    // allocate cursor
    cursor = new BtCursor;
    sqlite3BtreeCursorZero(cursor);
    rc = sqlite3BtreeCursor(db_, MASTER_ROOT, 1, 0, cursor);
    if (rc == SQLITE_OK) {
     //sqlite3BtreeEnterCursor(cursor);
     //sqlite3BtreeLeaveCursor(cursor);
     sqlite3BtreeCloseCursor(cursor);
    }

    delete cursor;
   }
  }

  rc = sqlite3BtreeCommit(db_);

  if (rc != SQLITE_OK) {
   return StatusFromSqlite(rc);
  }

  sqlite3BtreeLeave(db_);
 */

 Context::Context(sqlite3* conn, Btree* db, std::string name, base::FilePath path) : conn_(conn),
 db_(db),
 open_(true), 
 in_trans_(false),
 name_(std::move(name)),
 path_(std::move(path)) {

 DCHECK(conn);
 DCHECK(db);
}

Context::~Context() {

 if (open_)
  Close();

 delete conn_;
}

bool Context::is_readonly() const {
 auto i = sqlite3_db_readonly(conn_, path_.MaybeAsASCII().c_str());
 return i == 1 ? true : false;
}

Transaction Context::CreateTransaction(bool write) {
 return Transaction(this, write);
}

Table* Context::LoadTable(const std::string& name) {
 return nullptr;
}


Index* Context::LoadIndex(const std::string& name) {
 return nullptr;
}

void Context::Close() {
 auto rc = sqlite3BtreeClose(db_);
 if (rc != SQLITE_OK) {
  LOG(ERROR) << "failed to close the db btree handle";
 }
 open_ = false;
}

tableid_t Context::NewTableID() {
 return -1;
}

}