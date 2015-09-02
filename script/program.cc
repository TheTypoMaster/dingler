// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "script/program.h"

#include "script/script_context.h"

namespace script {

// static 
Program* Program::Load(ScriptContext* context, const std::string& script) {

}

// static 
Program* Program::Load(ScriptContext* context, const base::FilePath& file) {

}

Program::Program(ScriptContext* context) : context_(context),
 compiled_(false) {

}

Program::~Program() {

}

bool Program::Compile() {

}

Value* Program::Run() {
 return context_->RunBlock(&main_block_);
}

}