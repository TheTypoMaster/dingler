// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMON_FILE_DESCRIPTOR_INFO_IMPL_H_
#define COMMON_FILE_DESCRIPTOR_INFO_IMPL_H_

#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "common/file_descriptor_info.h"

namespace common {

class FileDescriptorInfoImpl : public FileDescriptorInfo {
 public:
  static scoped_ptr<FileDescriptorInfo> Create();

  ~FileDescriptorInfoImpl() override;
  void Share(int id, base::PlatformFile fd) override;
  void Transfer(int id, base::win::ScopedHandle fd) override;
  const base::FileHandleMappingVector& GetMapping() const override;
  base::FileHandleMappingVector GetMappingWithIDAdjustment(
      int delta) const override;
  base::PlatformFile GetFDAt(size_t i) const override;
  int GetIDAt(size_t i) const override;
  size_t GetMappingSize() const override;

 private:
  FileDescriptorInfoImpl();

  void AddToMapping(int id, base::PlatformFile fd);
  bool HasID(int id) const;
  base::FileHandleMappingVector mapping_;
  
  //ScopedVector<base::ScopedFD> owned_descriptors_;
  ScopedVector<base::win::ScopedHandle> owned_descriptors_;
};
}

#endif  // COMMON_FILE_DESCRIPTOR_INFO_IMPL_H_
