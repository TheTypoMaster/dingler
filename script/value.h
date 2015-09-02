// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SCRIPT_VALUE_H__
#define SCRIPT_VALUE_H__

#include "base/basictypes.h"

namespace script {

class Value {
public:
 virtual ~Value();
protected:
 Value();
private:
 DISALLOW_COPY_AND_ASSIGN(Value);
};

class StringValue : public Value {
public:
 StringValue();
 ~StringValue() override;
private:

};

}

#endif