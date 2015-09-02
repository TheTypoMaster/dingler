// Copyright 2010 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//
// Only to be included by test code.

#ifndef IMAGE_CURSOR_INFRASTRUCTURE_FILE_IO_INTERNAL_H_
#define IMAGE_CURSOR_INFRASTRUCTURE_FILE_IO_INTERNAL_H_

#include "image/query/base/result.h"
#include "image/query/base/types.h"

class File;

namespace image {

class View;

FailureOrVoid WriteViewWithMaxChunkRowCount(
    const View& view,
    const rowcount_t max_chunk_row_count,
    File* output_file);

}  // namespace image

#endif  // IMAGE_CURSOR_INFRASTRUCTURE_FILE_IO_INTERNAL_H_
