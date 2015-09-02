// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_NAMESPACE_IO_CONSOLE_H__
#define CONTAINER_HOST_NAMESPACE_IO_CONSOLE_H__

#include "container/host/namespace/resource.h"

namespace container {
 /*
  * Consoles oferecem uma interface mais sofisticada do que o stdin, stdout basicos
  * A ideia é suportar e gerenciar multiplos text buffers, além de um sistema de cores
  * e suporte de eventos de teclado, mouse, etc
  */
class Console : public Resource {
public:
 Console(UUID id);
 ~Console() override;

private:

};

}

#endif