// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SCRIPT_PROGRAM_H__
#define SCRIPT_PROGRAM_H__

#include <string>

#include "base/basictypes.h"
#include "base/files/file_path.h"
#include "script/block.h"

namespace script {
class ScriptContext;
class Value;

class Program {
public:
 static Program* Load(ScriptContext* context, const std::string& script);
 static Program* Load(ScriptContext* context, const base::FilePath& file);

 Program(ScriptContext* context);
 ~Program();

 bool compiled() const { return compiled_; }

 bool Compile();

 Value* Run();

private:
 
 ScriptContext* context_;

 Block   main_block_;

 bool compiled_;

 DISALLOW_COPY_AND_ASSIGN(Program);
};

}

#endif