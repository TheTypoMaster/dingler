// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DINGLER_DB_CONTEXT_H_
#define DINGLER_DB_CONTEXT_H_

#include <string>

#include "base/basictypes.h"
#include "base/files/file_path.h"
#include "base/containers/hash_tables.h"
#include "db/status.h"
#include "db/transaction.h"
#include "db/globals.h"
#include "third_party/bt/sqlite3.h"
#include "third_party/bt/sqliteInt.h"
#include "third_party/bt/btree.h"
#include "third_party/bt/btreeInt.h"

namespace db {
class Table;
class Index;
class Cursor;
class Schema;
class Mutator;

class Context {
public:
 Context(sqlite3* conn, Btree* db, std::string name, base::FilePath path);
 ~Context();

 bool is_open() const { return open_; }

 bool is_readonly() const;

 const std::string& db_name() const { return name_; }

 Transaction CreateTransaction(bool write);

 Table* LoadTable(const std::string& name);

 Index* LoadIndex(const std::string& name);

 void Close();

 tableid_t NewTableID();

private:
 friend class Mutator;
 friend class Transaction;

 std::string name_;

 base::FilePath path_;

 sqlite3* conn_;
 
 Btree*   db_;

 bool     open_;

 bool     in_trans_;

 DISALLOW_COPY_AND_ASSIGN(Context);
};

}

#endif
