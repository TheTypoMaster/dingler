// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/host/namespace/plugin/plugin_namespace.h"

namespace container {

PluginNamespace::PluginNamespace(UUID uuid) :
 Namespace(uuid, NamespaceType::Plugin) {

}

 PluginNamespace::~PluginNamespace() {

}

}