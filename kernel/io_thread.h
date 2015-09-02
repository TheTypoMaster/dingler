// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KERNEL_IO_THREAD_H__
#define KERNEL_IO_THREAD_H__

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/synchronization/waitable_event.h"
#include "kernel/kernel_thread_delegate.h"
#include "common/message_router.h"

class PrefRegistrySimple;

namespace kernel {
class CommandProcessHost;

class IOThread : public KernelThreadDelegate {
public:
 
 static void RegisterPrefs(PrefRegistrySimple* registry);

 IOThread();
 ~IOThread() override;
private:

 class IOThreadMessageRouter : public common::MessageRouter {
 public:
  // |sender| must outlive this object.
  explicit IOThreadMessageRouter(IPC::Sender* sender);
  bool Send(IPC::Message* msg) override;

 private:
  IPC::Sender* const sender_;
 };
 // KernelThreadDelegate
 void Init() override;
 void CleanUp() override;

 IOThreadMessageRouter router_;

 base::WaitableEvent shutdown_event_;

 scoped_ptr<CommandProcessHost> command_process_host_;

 const base::TimeTicks creation_time_;

 /*scoped_ptr<net::NetworkDelegate> system_network_delegate_;
 scoped_ptr<net::HostResolver> host_resolver_;
 scoped_ptr<net::CertVerifier> cert_verifier_;

 scoped_refptr<net::URLRequestContextGetter> url_request_context_getter_;

 scoped_ptr<net::URLRequestContext> proxy_script_fetcher_context_;*/

 base::WeakPtrFactory<IOThread> weak_factory_;

 DISALLOW_COPY_AND_ASSIGN(IOThread);
};

}

#endif
