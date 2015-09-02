// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "db/cursor.h"

#include "base/logging.h"
#include "db/table.h"
#include "third_party/bt/btreeInt.h"

namespace db {

Cursor::Cursor(Table* table, BtCursor* cursor) : table_(table),
 cursor_(cursor) {

}

Cursor::~Cursor() {

}

bool Cursor::is_valid() const {
#ifndef NDEBUG // as btree.h
 return sqlite3BtreeCursorIsValid(cursor_) == SQLITE_OK;
#endif
 return true;
}

size_t Cursor::Count() const {
 i64 count = 0;

 auto rc = sqlite3BtreeCount(cursor_, &count);
 DCHECK(rc);

 return count;
}

Status Cursor::Seek(SeekOp op) {
 return Status::Ok;
}

/* from vdbe.c:2617 -> 2599: case OP_MakeRecord: {
**
** Assuming the record contains N fields, the record format looks
** like this:
**
** ------------------------------------------------------------------------
** | hdr-size | type 0 | type 1 | ... | type N-1 | data0 | ... | data N-1 |
** ------------------------------------------------------------------------
**
** Data(0) is taken from register P1.  Data(1) comes from register P1+1
** and so forth.
*/

void Cursor::GetPayload(const void** payload, size_t* size) {
 u32 payload_size;
 u32 avail;
 //const void* payload;

 auto rc = sqlite3BtreeDataSize(cursor_, &payload_size);
 DCHECK(rc);

 // NOTE: parece que o payload pode ter um header
 // ou nao sei se é coisa apenas do SQLITE
 *payload = sqlite3BtreeDataFetch(cursor_, &avail);
 *size = payload_size;
}

}