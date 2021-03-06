// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DINGLER_IMAGE_QUERY_LANG_TOKEN_H_
#define DINGLER_IMAGE_QUERY_LANG_TOKEN_H_

namespace image {

enum class Token {
 EOF,
 Error,
 Newline,
 Colon,
 Name,
 Bool,
 Int,
 Float,
 String,
 Hex,
 Enum,
 List,
 Function,
 Object,
 ObjectField,
};

}

#endif