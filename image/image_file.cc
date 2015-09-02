// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "image/image_file.h"

#include "base/logging.h"
#include "image/index.h"

namespace image {

ImageFile* ImageFile::Create(const base::FilePath& path) {
 sqlite3* conn = new sqlite3;
 Btree* db;

 conn->pVfs = sqlite3_vfs_find(0);

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

 auto rc = sqlite3BtreeOpen(conn->pVfs, path.MaybeAsASCII().c_str(), conn, &db, 0,
  flags | SQLITE_OPEN_MAIN_DB);

 if (rc != SQLITE_OK)
  return nullptr;

 return new ImageFile(path, conn, db);
}

ImageFile* ImageFile::Open(const base::FilePath& path) {
 sqlite3* conn = new sqlite3;
 Btree* db;

 conn->pVfs = sqlite3_vfs_find(0);

 int flags = SQLITE_OPEN_READWRITE;
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

 auto rc = sqlite3BtreeOpen(conn->pVfs, path.MaybeAsASCII().c_str(), conn, &db, 0,
  flags | SQLITE_OPEN_MAIN_DB);

 if (rc != SQLITE_OK)
  return nullptr;

 return new ImageFile(path, conn, db);
}

bool ImageFile::Delete(const base::FilePath& path) {
 return false;
}

ImageFile::ImageFile(const base::FilePath& path, sqlite3* conn, Btree* db) : path_(path),
 conn_(conn), 
 db_(db),
 index_(new Index()) {
 
}

ImageFile::~ImageFile() {
 delete conn_;
}

void ImageFile::Close() {
 auto rc = sqlite3BtreeClose(db_);
 if (rc != SQLITE_OK) {
  LOG(ERROR) << "failed to close the db btree handle";
 }
}

}