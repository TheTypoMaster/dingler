// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KERNEL_SHELL_PREFS_KERNEL_PREFS_H_
#define KERNEL_SHELL_PREFS_KERNEL_PREFS_H_

class PrefRegistrySimple;
class PrefService;

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace kernel {
class KernelProcess;
// Register all prefs that will be used via the local state PrefService.
void RegisterLocalState(PrefRegistrySimple* registry);

}  // namespace kernel

#endif  // STRIPES_MODULES_SHELL_PREFS_BROWSER_PREFS_H_
