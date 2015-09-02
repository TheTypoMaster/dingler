// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DINGLER_DB_MUTATOR_H_
#define DINGLER_DB_MUTATOR_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_vector.h"
#include "db/globals.h"
#include "db/status.h"

namespace db {
class Context;
class Table;
class Row;
class Schema;
class Index;

// Use it to change a table data
class Mutator {
public:
 Mutator(Context* context);
 ~Mutator();

 // rows
 Status InsertRow(Table* table, const Row* r);
 Status DeleteRow(Table* table, rowid_t rowid);

 Status CreateTable(const std::string& name, const Schema& schema, Table** out);
 Status ClearTable(Table* table);
 Status DropTable(Table* table);

 Status CreateIndex(const std::string& name, Index** out);
 Status DropIndex(const std::string& name);

private:
 Context* context_;

 DISALLOW_COPY_AND_ASSIGN(Mutator);
};

}

#endif
