// Copyright 2012 Google Inc.  All Rights Reserved
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
// Author: tomasz.kaftal@gmail.com (Tomasz Kaftal)
//
// File contains a class for cursor transformers which maintain a history of
// transformations.
#ifndef IMAGE_CURSOR_INFRASTRUCTURE_HISTORY_TRANSFORMER_H_
#define IMAGE_CURSOR_INFRASTRUCTURE_HISTORY_TRANSFORMER_H_

#include <memory>

#include "image/query/cursor/cursor_transformer.h"
#include "image/query/cursor/ownership_revoker.h"

#include "base/logging.h"
#include "image/query/utils/macros.h"
#include "image/query/utils/pointer_vector.h"

namespace image {

// An abstract class providing implementation for history utilities using
// a PointerVector. The T-class objects are stored in a PointerVector
// and cleaned when the transformer is destroyed, or when a call
// to CleanHistory() is made. The caller may take ownership of the entire
// history vector by calling the ReleaseHistory() method.
template<typename T>
class CursorTransformerWithVectorHistory : public CursorTransformer {
 public:
  CursorTransformerWithVectorHistory()
      : CursorTransformer(),
        run_history_(new gtl::PointerVector<T>) {}

  size_t GetHistoryLength() const {
    return run_history_->size();
  }

  // Ownership is not transferred.
  T* GetEntryAt(size_t position) const {
    CHECK_LT(position, run_history_->size());
    return (*run_history_)[position].get();
  }

  // Ownership is not transferred.
  T* GetFirstEntry() const {
    CHECK_GT(run_history_->size(), 0);
    return run_history_->front().get();
  }

  // Ownership is not transferred.
  T* GetLastEntry() const {
    CHECK_GT(run_history_->size(), 0);
    return run_history_->back().get();
  }

  // Cleans the history and takes care of cleaning up the entries.
  void CleanHistory() {
    run_history_->clear();
  }

  // Returns the disembodied history vector and replaces it internally with
  // a new empty one.
  gtl::PointerVector<T>* ReleaseHistory() {
    using util::gtl::PointerVector;
    std::unique_ptr<PointerVector<T> > internal(new PointerVector<T>);
    internal.swap(run_history_);
    return internal.release();
  }

 protected:
  std::unique_ptr<gtl::PointerVector<T> > run_history_;
};

typedef OwnershipRevoker<Cursor> CursorOwnershipRevoker;

typedef CursorTransformerWithVectorHistory<CursorOwnershipRevoker>
CursorTransformerWithSimpleHistory;

}  // namespace image
#endif  // IMAGE_CURSOR_INFRASTRUCTURE_HISTORY_TRANSFORMER_H_
