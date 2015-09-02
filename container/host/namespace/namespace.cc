// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <algorithm>

#include "container/common/constants.h"
#include "container/host/namespace/namespace.h"
#include "container/host/namespace/namespace_view.h"
#include "container/host/namespace/namespace_index.h"

namespace container {

Namespace::Namespace(UUID id, NamespaceType type) :
 id_(std::move(id)), 
 type_(type),
 used_size_(0),
 allocated_size_(0),
 elem_count_(0),
 encrypted_(false),
 compressed_(false) {

}
 
Namespace::~Namespace() {

}

status::Code Namespace::Init() {
 return status::Code::Undefined;
}

NamespaceView* Namespace::GetView(const std::string& name) const {
 return views_.at(name);
}

void Namespace::AddView(std::string name, NamespaceView* view) {
 views_[std::move(name)] = view;
}

void Namespace::RemoveView(const std::string& name) {
 auto view = views_.at(name);
 if (view) {
  views_.erase(name);
  delete view;
 }
}

}