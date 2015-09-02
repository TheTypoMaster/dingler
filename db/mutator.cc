// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "db/mutator.h"

#include "db/context.h"
#include "db/table.h"
#include "db/row.h"
#include "db/transaction.h"

namespace db {

Mutator::Mutator(Context* context): context_(context) {

}

Mutator::~Mutator() {

}

Status Mutator::CreateTable(const std::string& name, const Schema& schema, Table** out) {
 
 int pgno;
 auto rc = sqlite3BtreeCreateTable(context_->db_, &pgno, BTREE_INTKEY);
 if (rc != SQLITE_OK)
  return StatusFromSqlite(rc);

 Table* t = new Table(context_, pgno, name, schema);

 *out = t;

 return Status::Ok;
}

Status Mutator::DropTable(Table* table) {

 // 1 - delete table in the on-disk btree
 // 2 - remove the reference on the hash table
 // 3 - delete the heap allocated table ptr
 int r;
 auto rc = sqlite3BtreeDropTable(context_->db_, table->id(), &r);
 if (rc != SQLITE_OK)
  return StatusFromSqlite(rc);

 return Status::Ok;
}

Status Mutator::CreateIndex(const std::string& name, Index** out) {

 // sqlite3BtreeCreateIndex()

 return Status::Ok;
}

Status Mutator::DropIndex(const std::string& name) {
 return Status::Ok;
}

/** A write - transaction must be started before attempting any
** changes to the database.None of the following routines
** will work unless a transaction is started first :
**
**      sqlite3BtreeCreateTable()
**      sqlite3BtreeCreateIndex()
**      sqlite3BtreeClearTable()
**      sqlite3BtreeDropTable()
**      sqlite3BtreeInsert()
**      sqlite3BtreeDelete()
**      sqlite3BtreeUpdateMeta() */

Status Mutator::InsertRow(Table* table, const Row* r) {
 // sqlite3BtreeInsert();
 return Status::Ok;
}

Status Mutator::DeleteRow(Table* table, rowid_t rowid) {
 // sqlite3BtreeDelete()
 return Status::Ok;
}

Status Mutator::ClearTable(Table* table) {
 // sqlite3BtreeClearTable()
 return Status::Ok;
}


}