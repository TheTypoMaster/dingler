// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "script/script_engine.h"

#include "v8/include/v8.h"
#include "v8/include/libplatform/libplatform.h"
#include "script/script_context.h"

namespace script {

ScriptEngine::ScriptEngine(): platform_(v8::platform::CreateDefaultPlatform()) {

}

ScriptEngine::~ScriptEngine() {
 isolate_->Dispose();
 v8::V8::Dispose();
 v8::V8::ShutdownPlatform();
}

bool ScriptEngine::Init() {
 v8::V8::InitializeICU();
 v8::V8::InitializePlatform(platform_.get());
 v8::V8::Initialize();

 isolate_ = v8::Isolate::New();
}

ScriptContext* ScriptEngine::CreateContext() {
 return new ScriptContext(this, v8::Context::New(isolate_));
}

}