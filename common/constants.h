// Copyright (c) 2014 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMON_CONSTANTS_H_
#define COMMON_CONSTANTS_H_

#include "base/files/file_path.h"

namespace constants {

extern const base::FilePath::CharType kLocalStorePoolName[];
extern const base::FilePath::CharType kKernelProcessExecutableName[];
extern const base::FilePath::CharType kSingletonCookieFilename[];
extern const base::FilePath::CharType kSingletonSocketFilename[];
extern const base::FilePath::CharType kSingletonLockFilename[];
extern const base::FilePath::CharType kPreferencesFilename[];


}

#endif
