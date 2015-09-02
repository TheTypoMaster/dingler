// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SCRIPT_SCRIPT_ENGINE_H__
#define SCRIPT_SCRIPT_ENGINE_H__

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"

namespace v8 {
class Platform;
class Isolate;
}

namespace script {
class ScriptContext;

class ScriptEngine {
public:
 ScriptEngine();
 ~ScriptEngine();

 bool Init();

 ScriptContext* CreateContext();

private:
 friend class ScriptContext;

 scoped_ptr<v8::Platform> platform_;
 //for simplicity only one isolate
 v8::Isolate* isolate_;

 DISALLOW_COPY_AND_ASSIGN(ScriptEngine);
};

}

#endif