// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "kernel/io_thread.h"

#include "base/prefs/pref_registry_simple.h"
#include "base/prefs/pref_service.h"
#include "common/switches.h"
#include "kernel/kernel_thread.h"
#include "kernel/command_host/command_process_host.h"

namespace kernel {

 // static
void IOThread::RegisterPrefs(PrefRegistrySimple* registry) {
 //registry->RegisterBooleanPref(prefs::kEnableReferrers, true);
}

IOThread::IOThreadMessageRouter::IOThreadMessageRouter(
 IPC::Sender* sender)
 : sender_(sender) {}

bool IOThread::IOThreadMessageRouter::Send(IPC::Message* msg) {
 return sender_->Send(msg);
}

IOThread::IOThread() : shutdown_event_(true, false),
  creation_time_(base::TimeTicks::Now()),
  router_(nullptr), // TODO: check this later.. can brake things
  weak_factory_(this) {
 KernelThread::SetDelegate(KernelThread::IO, this);
}

IOThread::~IOThread() {
 KernelThread::SetDelegate(KernelThread::IO, NULL);
}

void IOThread::Init()  {
 CHECK(KernelThread::CurrentlyOn(KernelThread::IO));

 //scoped_ptr<KernelNetworkDelegate> kernel_network_delegate(
 // new KernelNetworkDelegate(//extension_event_router_forwarder(),
 // &system_enable_referrers_));
 //Send(new ShellHostMsg_Initialized);
 command_process_host_.reset(new CommandProcessHost());

 command_process_host_->Init();

 /*system_network_delegate_ = kernel_network_delegate.Pass();
 host_resolver_ = CreateHostResolver(net_log_);

 cert_verifier_.reset(new net::MultiThreadedCertVerifier(
  net::CertVerifyProc::CreateDefault()));

 proxy_script_fetcher_context_.reset(
  ConstructProxyScriptFetcherContext(this, net_log_));*/
}

void IOThread::CleanUp() {
 command_process_host_.reset();
}

}
