// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DINGLER_DB_TRANSACTION_H_
#define DINGLER_DB_TRANSACTION_H_

#include "db/status.h"

namespace db {
class Context;

class Transaction {
public:
 Transaction(Context* context, bool write);
 ~Transaction();

 bool is_write() const { return write_; }

 Context* context() const { return context_; }

 Status Begin();
 Status Rollback();
 Status Commit();

private:

 Context* context_;

 bool write_;
};

}

#endif