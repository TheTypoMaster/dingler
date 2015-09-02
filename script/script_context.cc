// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <algorithm>

#include "script/script_context.h"
#include "script/script_engine.h"

namespace script {

ScriptContext::ScriptContext(ScriptEngine* engine, v8::Local<v8::Context> context) : 
 engine_(engine), 
 context_(std::move(context)) {

}

ScriptContext::~ScriptContext() {

}


Value* ScriptContext::RunBlock(Block* block) {
 v8::Isolate::Scope isolate_scope(engine_->isolate_);
 v8::Context::Scope context_scope(context_);
}


Value* ScriptContext::RunFunction(Function* fn) {

}

}