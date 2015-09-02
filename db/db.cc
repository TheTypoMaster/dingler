// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "db/db.h"

#include "base/files/file_util.h"
#include "db/context.h"

namespace db {

 Status Open(const base::FilePath& path, std::string db_name, Context** out) {
 sqlite3* conn = new sqlite3;
 Btree* db;

 conn->pVfs = sqlite3_vfs_find(0);

 DCHECK(conn->pVfs);

 int flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
 flags &= ~(SQLITE_OPEN_EXCLUSIVE |
  SQLITE_OPEN_MAIN_DB |
  SQLITE_OPEN_TEMP_DB |
  SQLITE_OPEN_TRANSIENT_DB |
  SQLITE_OPEN_MAIN_JOURNAL |
  SQLITE_OPEN_TEMP_JOURNAL |
  SQLITE_OPEN_SUBJOURNAL |
  SQLITE_OPEN_MASTER_JOURNAL |
  SQLITE_OPEN_NOMUTEX |
  SQLITE_OPEN_FULLMUTEX |
  SQLITE_OPEN_WAL
  );

 auto rc = sqlite3BtreeOpen(conn->pVfs, path.AppendASCII(db_name).MaybeAsASCII().c_str(), conn, &db, 0,
  flags | SQLITE_OPEN_MAIN_DB);

 if (rc != SQLITE_OK)
  return StatusFromSqlite(rc);

 *out = new Context(conn, db, db_name, path);

 return Status::Ok;
}

Status Delete(const base::FilePath& path, const std::string& name) {
 return Status::Ok;
 //return base::DeleteFile(path, false) ? Status::Ok : Status::Error;
}

}