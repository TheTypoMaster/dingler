// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_CLIENT_CONTAINER_NAVIGATOR_H__
#define CONTAINER_CLIENT_CONTAINER_NAVIGATOR_H__

#include "base/basictypes.h"
#include "url/gurl.h"

namespace container {
class ContainerClient;
class ResultSet;

class ContainerNavigator {
public:
 ContainerNavigator(ContainerClient* client);
 ~ContainerNavigator();

 ContainerClient* client() const { return client_; }

 GURL* current() const { return current_; }

 ResultSet* Go(const GURL& url);

private:

 ContainerClient* client_;

 GURL* current_;

 DISALLOW_COPY_AND_ASSIGN(ContainerNavigator);
};

}

#endif