// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "container/client/container_navigator.h"

#include "container/client/result_set.h"

namespace container {

ContainerNavigator::ContainerNavigator(ContainerClient* client) : client_(client),
 current_(nullptr){

}
 
ContainerNavigator::~ContainerNavigator() {

}

ResultSet* ContainerNavigator::Go(const GURL& url) {

}

}