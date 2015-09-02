// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_NAMESPACE_H__
#define CONTAINER_HOST_NAMESPACE_NAMESPACE_H__

#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/containers/hash_tables.h"
#include "container/common/uuid.h"
#include "common/status.h"

//
// Namespaces - Agora deverão ser modelados no protobuf, e nao mais no C++
// para cada tipo de namespace teremos um arquivo .proto definindo o seu layout
// e o seu comportamento.
// Isso também permite que os usuários criem namespaces adaptados as suas realidades
// bastando usar o protobuf
//
namespace container {
class NamespaceIndex;
class NamespaceView;

enum class NamespaceType {
 Root       = 0,
 Sys        = 1,
 IO         = 2,
 Device     = 3,
 Process    = 4,
 Container  = 5,
 Service    = 6,
 Blob       = 7,
 Run        = 8,
 KV         = 9,
 UUID       = 10,
 Credential = 11,
 Stats      = 12,
 Index      = 13, // A fulltext search index (future)
 Wallet     = 14,
 Social     = 15,
 Plugin     = 16,
 Last       = Plugin
};

class Namespace {
public:
 virtual ~Namespace();

 const UUID& id() const { return id_; }
 
 NamespaceType type() const { return type_; }

 size_t used_size() const { return used_size_; }
 
 size_t allocated_size() const { return allocated_size_; }
 
 size_t elem_count() const { return elem_count_; }
 
 bool encrypted() const { return encrypted_; }

 bool compressed() const { return compressed_; }

 NamespaceIndex* index() const { return index_.get(); }

 virtual status::Code Init();

 NamespaceView* GetView(const std::string& name) const;
 void AddView(std::string name, NamespaceView* view);
 void RemoveView(const std::string& name);
 
 //  TODO: what are the generic actions allowed to interact with 
 //        resources? TOUCH, GET, PUT, etc..

protected:

 Namespace(UUID id, NamespaceType type);
 
 typedef base::hash_map<std::string, NamespaceView *> Views;

 Views views_;

 UUID id_;

 NamespaceType type_;

 scoped_ptr<NamespaceIndex> index_;

 size_t used_size_;

 size_t allocated_size_;

 size_t elem_count_;

 bool encrypted_;

 bool compressed_;

private:

 DISALLOW_COPY_AND_ASSIGN(Namespace);
};

}

#endif