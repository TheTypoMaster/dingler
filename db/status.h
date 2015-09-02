// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DINGLER_DB_STATUS_H_
#define DINGLER_DB_STATUS_H_

#include "base/logging.h"
#include "third_party/bt/sqlite3.h"

namespace db {

 /*
 *
 #define SQLITE_OK           0    Successful result
 #define SQLITE_ERROR        1    SQL error or missing database
 #define SQLITE_INTERNAL     2    Internal logic error in SQLite
 #define SQLITE_PERM         3    Access permission denied
 #define SQLITE_ABORT        4    Callback routine requested an abort
 #define SQLITE_BUSY         5    The database file is locked
 #define SQLITE_LOCKED       6    A table in the database is locked
 #define SQLITE_NOMEM        7    A malloc() failed
 #define SQLITE_READONLY     8    Attempt to write a readonly database
 #define SQLITE_INTERRUPT    9    Operation terminated by sqlite3_interrupt()
 #define SQLITE_IOERR       10    Some kind of disk I/O error occurred
 #define SQLITE_CORRUPT     11    The database disk image is malformed
 #define SQLITE_NOTFOUND    12    Unknown opcode in sqlite3_file_control()
 #define SQLITE_FULL        13    Insertion failed because database is full
 #define SQLITE_CANTOPEN    14    Unable to open the database file
 #define SQLITE_PROTOCOL    15    Database lock protocol error
 #define SQLITE_EMPTY       16    Database is empty
 #define SQLITE_SCHEMA      17    The database schema changed
 #define SQLITE_TOOBIG      18    String or BLOB exceeds size limit
 #define SQLITE_CONSTRAINT  19    Abort due to constraint violation
 #define SQLITE_MISMATCH    20    Data type mismatch
 #define SQLITE_MISUSE      21    Library used incorrectly
 #define SQLITE_NOLFS       22    Uses OS features not supported on host
 #define SQLITE_AUTH        23    Authorization denied
 #define SQLITE_FORMAT      24    Auxiliary database format error
 #define SQLITE_RANGE       25    2nd parameter to sqlite3_bind out of range
 #define SQLITE_NOTADB      26    File opened that is not a database file
 #define SQLITE_NOTICE      27    Notifications from sqlite3_log()
 #define SQLITE_WARNING     28    Warnings from sqlite3_log()
 #define SQLITE_ROW         100   sqlite3_step() has another row ready
 #define SQLITE_DONE        101   sqlite3_step() has finished executing
 */

enum class Status {
 Ok = 0,
 Error = 1,
 InternalErr = 2,
 PermErr = 3,
 AbortErr = 4,
 BusyErr = 5,
 LockedErr = 6,
 NoMemErr = 7,
 ReadOnlyErr = 8,
 InterruptErr = 9,
 IOErr = 10,
 CorruptErr = 11,
 NotFoundErr = 12,
 FullErr = 13,
 CantOpenErr = 14,
 ProtocolErr = 15,
 EmptyErr = 16,
 SchemaErr = 17,
 TooBigErr = 18,
 ConstraintErr = 19,
 MismatchErr = 20,
 MisuseErr = 21,
 NoLFSErr = 22,
 AuthErr = 23,
 FormatErr = 24,
 RangeErr = 25,
 NotADBErr = 26,
 Notice = 27,
 Warning = 28,
 Row = 100,
 Done = 101,
 MAX = Done
};

inline Status StatusFromSqlite(int code) {
 // should be in range
 DCHECK(code <= static_cast<int>(Status::MAX));

 return static_cast<Status>(code);
}

}

#endif