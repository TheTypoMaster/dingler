// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DINGLER_DB_DB_H_
#define DINGLER_DB_DB_H_

#include <string>

#include "base/basictypes.h"
#include "base/files/file_path.h"
#include "db/status.h"

namespace db {
class Context;
 
Status Open(const base::FilePath& path, std::string db_name, Context** out);
Status Delete(const base::FilePath& path, const std::string& name);

}

#endif