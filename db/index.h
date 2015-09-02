// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DINGLER_DB_INDEX_H_
#define DINGLER_DB_INDEX_H_

#include <string>

#include "base/basictypes.h"

namespace db {
class Table;
class Index {
public:
 enum class Type {
  Common,
  Unique,
  Primary
 };
 Index(Table* table, Type type, const std::string& name);
 ~Index();

 const std::string& name() const { return name_; }

 size_t column_count() const { return column_count_; }

 Type type() const { return type_; }

 bool is_primary_key() const { return type_ == Type::Primary; }

 bool is_unique_key() const { return type_ == Type::Unique; }

private:

 std::string name_;

 Table* table_;

 size_t column_count_;

 Type  type_;

 DISALLOW_COPY_AND_ASSIGN(Index);
};

}

#endif