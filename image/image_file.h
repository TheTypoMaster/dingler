// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DINGLER_IMAGE_IMAGE_FILE_H_
#define DINGLER_IMAGE_IMAGE_FILE_H_

#include "base/basictypes.h"
#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "third_party/bt/sqlite3.h"
#include "third_party/bt/sqliteInt.h"
#include "third_party/bt/btree.h"
#include "third_party/bt/btreeInt.h"

namespace image {
class Index;

class ImageFile {
public:
 static ImageFile* Create(const base::FilePath& path);
 static ImageFile* Open(const base::FilePath& path);
 static bool Delete(const base::FilePath& path);

 ~ImageFile();

 Index* index() const { return index_.get(); }

 void Close();

private:
 ImageFile(const base::FilePath& path, sqlite3* conn, Btree* db);

 base::FilePath path_;

 sqlite3* conn_;

 Btree*   db_;

 scoped_ptr<Index> index_;

 DISALLOW_COPY_AND_ASSIGN(ImageFile);
};

}

#endif //DINGLER_IMAGE_FILE_H_
