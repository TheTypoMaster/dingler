// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_CLIENT_RESULT_SET_H__
#define CONTAINER_CLIENT_RESULT_SET_H__

#include "base/basictypes.h"
#include "base/files/file_path.h"
#include "container/common/uuid.h"

namespace container {

enum class ResultCode {
 UNDEFINED = -1,
 OK        = 0,
 NOT_FOUND = 1,
};

// A filesystem resultset
// TODO: o cursor deve ser ninja
// a ideia é que possamos tanto
// listar qualquer tipo de elemento
// até mesmo do http

class ResultSet {
public:
 ResultSet();
 ~ResultSet();

 ResultCode code() const { return code_; }
 
 bool ok() const { return code_ == ResultCode::OK; }

 // print to the given stream, the resource
 // must be a valid stream resource from the IOFS
 // ex: stdout
 void PrintTo(const UUID& stream) const;

private:

 ResultCode code_;

 DISALLOW_COPY_AND_ASSIGN(ResultSet);
};

}

#endif