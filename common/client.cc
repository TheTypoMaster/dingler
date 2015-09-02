// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "common/client.h"

namespace common {

static Client* g_client;

Client::Client(): kernel_client_(nullptr),
                  application_client_(nullptr),
                  container_client_(nullptr) {

}

Client::~Client() {

}

Client* GetClient() {
 return g_client;
}

void SetClient(Client* client) {
 g_client = client;
}

}