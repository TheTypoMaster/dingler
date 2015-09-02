// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_ROOT_ROOT_NODE_H__
#define CONTAINER_HOST_NAMESPACE_ROOT_ROOT_NODE_H__

#include "container/host/namespace/resource.h"
#include "base/strings/string16.h"
#include "base/files/file_path.h"

namespace container {
 /*
  * The root fs is the head filesystem of each volume
  * and others filesystems are mounted as a child of the rootfs
  * so the nodes of a rootfs represent the others filesystems
  * embedded on it.
  * 
  *(Volume X)
  * (RootNS) - "twitter:root/"
  *          |
  *           --- "twitter:sys/"      (SysNS)
  *           --- "twitter:device/"   (DeviceNS)
  *           --- "twitter:io/"       (IONS)
  *           --- "twitter:process/"  (ProcessNS)
  *           --- "twitter:service/"  (ServiceNS)
  *           --- "twitter:uuid/"     (UUIDNS)  
  *           --- "twitter:user/"     (CredNS)
  *           --- "twitter:globals/"  (KVNS)
  *           --- "twitter:cmd/"      (RunNS)
  *           --- "twitter:app/"      (RunNS)
  *           --- "twitter:bundle/"   (BundleNS)  for app bundles
  *           --- "twitter:music/"    (BlobNS)
  *           --- "twitter:movies/"   (BlobNS)
  *           --- "twitter:pics/"     (BlobNS)
  *           --- "twitter:wallet/"   (WalletNS)
  *           --- "twitter:social/"   (SocialNS)
  *           --- "twitter:index/"    (Fulltext Search Index)
  *           --- "twitter:tags/"     (KVNS) tags: { greetings } => { data: 'howdy there!' }
  *                                   #greetings(=tags:greetings) => 'howdy there!'  
  *           --- "twitter:hello/"    (PluginNS)
  *                           hello: { say: "hello" } => will route to a service(or node)
  *                                                 defined by the user (or whatever)
  *
  * so here each first level name map to a namespace in the container
  *
  * NOTE: everything must be reachable by '/common/path' to ensure compability
  * with tools that already use the filesystem
  * 
  * NOTE 2: these namespaces are only accessible by the applications launched
  * by the namespaces, or the child applications, externally other actors
  * can only see the public nodes
  * What can be seeing by apps or users are defined by the auth tokens given to them
  * A application lanched has a auth token that gives it access to the private members
  * of a container, a user actor, with the right credentials can also see and perhaps
  * manipulate the resources inside a container
  */

enum class RootNodeVisibility {
 Undefined,
 Private,
 Public
};

class RootNode : public Resource {
public:
 RootNode(UUID uuid);
 ~RootNode() override;

 RootNodeVisibility visibility() const { return visibility_; }
 // 
 const base::string16& name() const { return name_; }
 // absolute path
 // "hello:world"
 const base::FilePath& path() const { return path_; }

 // TODO: introspection api
 // we need to expose ways for the user to
 // see the bits of a given node of the RootFS

 // $ from("hello:all").select("name, type").where("name == 'hello'");

private:

 base::string16 name_;
 
 base::FilePath path_;

 RootNodeVisibility visibility_;

 DISALLOW_COPY_AND_ASSIGN(RootNode);
};

}

#endif