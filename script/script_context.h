// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SCRIPT_SCRIPT_CONTEXT_H__
#define SCRIPT_SCRIPT_CONTEXT_H__

#include <string>

#include "base/basictypes.h"
#include "v8/include/v8.h"

namespace script {
class ScriptEngine;
class Block;
class Function;
class Value;

class ScriptContext {
public:
 ~ScriptContext();

 // run a block of code
 Value* RunBlock(Block* block);
 // run a specific function
 Value* RunFunction(Function* fn);

private:
 friend class ScriptEngine;

 ScriptContext(ScriptEngine* engine, v8::Local<v8::Context> context);

 ScriptEngine* engine_;

 v8::Local<v8::Context> context_;

 DISALLOW_COPY_AND_ASSIGN(ScriptContext);
};

}

#endif