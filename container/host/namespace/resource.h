// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_RESOURCE_H__
#define CONTAINER_HOST_NAMESPACE_RESOURCE_H__

#include <string>

#include "base/basictypes.h"
#include "container/common/uuid.h"

namespace container {

enum class ResourceType {
 Run,
 Blob,
 Credential,
 Container,
 Device,
 IO,
 KV,
 Plugin,
 Process,
 Root,
 Service,
 Social,
 Stats,
 Sys,
 UUID,
 Wallet
};

enum class SpecialMode {
 Ordinary,
 System,
 Singleton
};

class Resource {
public:
 virtual ~Resource();

 // well.. the ubiquotous uuid, who would guess that..
 const UUID& id() const { return id_; }

 ResourceType type() const { return type_; }

 SpecialMode special_mode() const { return special_; }

 // can we have only one copy of this?
 bool is_singleton() const { return special_ == SpecialMode::Singleton; }
 // rootfs nodes, sys nodes, etc
 bool is_system() const { return special_ == SpecialMode::System; }

 bool is_readonly() const { return readonly_; }

 void set_readonly(bool readonly) { readonly_ = readonly; }

protected:
 Resource(UUID id, ResourceType type);
 Resource(UUID id, ResourceType type, SpecialMode special_mode);

private:
 UUID id_;

 ResourceType type_;

 SpecialMode special_;

 bool readonly_;

 DISALLOW_COPY_AND_ASSIGN(Resource);
};

}

#endif