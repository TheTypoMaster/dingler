// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KERNEL_CONTAINER_CONTAINER_CATALOG_H__
#define KERNEL_CONTAINER_CONTAINER_CATALOG_H__

#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/files/file_path.h"
#include "common/status.h"

namespace db {
class Context;
}

namespace kernel {
class Container;

class ContainerCatalog {
public:
 ContainerCatalog();
 ~ContainerCatalog();

 status::Code CreateContainer(const std::string& name, 
  Container** out);
 status::Code LoadContainer(const std::string& name,
  Container** out);
 status::Code DropContainer(const std::string& name);

private:

 scoped_ptr<db::Context> db_;

 DISALLOW_COPY_AND_ASSIGN(ContainerCatalog);
};

}

#endif