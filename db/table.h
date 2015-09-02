// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DINGLER_DB_TABLE_H_
#define DINGLER_DB_TABLE_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "db/globals.h"
#include "db/status.h"
#include "db/schema.h"

namespace db {
class Cursor;
class Index;
class Context;
class Row;

class Table {
public:
 
 Table(Context* context, 
   tableid_t id, 
   std::string name, 
   Schema schema);

 ~Table();

 Context* context() const { return context_; }

 tableid_t id() const { return id_; }

 const Schema& schema() const { return schema_; }

 rowid_t GetLastRowID() const;

 Index* GetPrimaryKeyIndex() const;

 scoped_ptr<Cursor> CreateCursor();

 Row* NewRow();

private:
 
 Context* context_;

 Schema schema_;

 tableid_t id_;

 std::string name_;

 DISALLOW_COPY_AND_ASSIGN(Table);
};

}

#endif