// Copyright (c) 2014 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "common/constants.h"
#include "base/files/file_path.h"

#define FPL FILE_PATH_LITERAL

namespace constants {

const base::FilePath::CharType kLocalStorePoolName[] = FPL("local_store_pool");
const base::FilePath::CharType kKernelProcessExecutableName[] = FPL("dingler");
const base::FilePath::CharType kSingletonCookieFilename[] = FPL("singleton_cookie");
const base::FilePath::CharType kSingletonSocketFilename[] = FPL("singleton_socket");
const base::FilePath::CharType kSingletonLockFilename[] = FPL("singleton_lock");
const base::FilePath::CharType kPreferencesFilename[] = FPL("prefs");


}

