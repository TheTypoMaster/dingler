// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_HOST_CONTAINER_H__
#define CONTAINER_HOST_CONTAINER_H__

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "ipc/ipc_sender.h"
#include "ipc/ipc_listener.h"

namespace container {
class VolumeDrive;
class VolumePool;

//
// TODO: define management api´s
// then let the kernel process use them at will
// ALSO: we need to also define the interface
// with the applications.
// So a container "obey" a master which is the kernel
// with the management apis
// and nanny the applications, serving resources to them
// and checking the policies for each one
// 
class Container : public IPC::Sender,
                  public IPC::Listener {
public:
 Container();
 ~Container() override;

 VolumeDrive* volume_drive() const { return volume_drive_.get(); }

 VolumePool* volume_pool() const { return volume_pool_.get(); }

 // TODO: implement the actions here (start, stop, etc)

 // MANAGEMENT API: kernel requests to us

 // SERVICE/EVENTS API: applications requests to us

 // Sender overrides
 bool Send(IPC::Message* msg) override;

private:
 // Listener overrides
 bool OnMessageReceived(const IPC::Message& message) override;
 void OnChannelConnected(int32 peer_pid) override;
 void OnChannelError() override;
 void OnBadMessageReceived(const IPC::Message& message) override;

 scoped_ptr<VolumeDrive> volume_drive_;

 scoped_ptr<VolumePool> volume_pool_;

 DISALLOW_COPY_AND_ASSIGN(Container);
};

}


#endif