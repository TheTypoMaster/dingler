// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "db/transaction.h"

#include "db/context.h"
#include "third_party/bt/sqlite3.h"
#include "third_party/bt/sqliteInt.h"
#include "third_party/bt/btree.h"

namespace db {

Transaction::Transaction(Context* context, bool write) : context_(context),
 write_(write) {

}

Transaction::~Transaction() {

}

Status Transaction::Begin() {
 auto rc = sqlite3BtreeBeginTrans(context_->db_, write_ ? 1 : 0);

 if (rc != SQLITE_OK)
  return StatusFromSqlite(rc);

 return Status::Ok;
}

Status Transaction::Rollback() {
 auto rc = sqlite3BtreeRollback(context_->db_, SQLITE_OK, 0);
 return StatusFromSqlite(rc);
}

Status Transaction::Commit() {
 auto rc = sqlite3BtreeCommit(context_->db_);
 return StatusFromSqlite(rc);
}

}