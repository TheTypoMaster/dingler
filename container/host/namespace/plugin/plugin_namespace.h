// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_PLUGIN_PLUGIN_NAMESPACE_H__
#define CONTAINER_HOST_NAMESPACE_PLUGIN_PLUGIN_NAMESPACE_H__

#include "container/host/namespace/namespace.h"

namespace container {
/* Plugin Namespace -
 *
 * A customized namespace
 *
 * hello:message=world
 * and in the "hello:" node we have 
 * a filter that process the request, and
 * send the parameters back to a given service
 * or another node, or do whatever you want
 */
class PluginNamespace : public Namespace {
public:
 PluginNamespace(UUID uuid);
 ~PluginNamespace() override;

private:

};

}

#endif