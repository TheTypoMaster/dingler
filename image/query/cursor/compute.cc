// Copyright 2010 Google Inc.  All Rights Reserved
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

#include "image/query/cursor/compute.h"

#include <memory>

#include "base/memory/scoped_ptr.h"
#include "image/query/utils/macros.h"
#include "image/query/utils/failureor.h"
#include "image/query/base/exception.h"
#include "image/query/base/exception_macros.h"
#include "image/query/cursor/cursor.h"
#include "image/query/cursor/cursors.pb.h"
#include "image/query/cursor/operation.h"
#include "image/query/cursor/basic_cursor.h"
#include "image/query/cursor/basic_operation.h"
#include "image/query/expression/expression.h"

namespace image {

class BufferAllocator;

namespace {

class ComputeCursor : public BasicCursor {
 public:
  ComputeCursor(BoundExpressionTree* computation,
                rowcount_t row_capacity,
                Cursor* child)
      : BasicCursor(computation->result_schema(), child),
        row_capacity_(row_capacity),
        computation_(computation) {}

  virtual ~ComputeCursor() {}

  virtual ResultView Next(rowcount_t max_row_count) {
    if (max_row_count > row_capacity_) max_row_count = row_capacity_;
    ResultView result = child()->Next(max_row_count);
    if (!result.has_data()) return result;
    EvaluationResult evaluated = computation_->Evaluate(result.view());
    PROPAGATE_ON_FAILURE(evaluated);
    return ResultView::Success(&evaluated.get());
  }

  virtual bool IsWaitingOnBarrierSupported() const { return true; }

  virtual CursorId GetCursorId() const { return COMPUTE; }

 private:
  const int row_capacity_;
  std::unique_ptr<BoundExpressionTree> computation_;
  DISALLOW_COPY_AND_ASSIGN(ComputeCursor);
};

class ComputeOperation : public BasicOperation {
 public:
  ComputeOperation(const Expression* computation, Operation* child)
      : BasicOperation(child),
        computation_(computation) {}

  virtual FailureOrOwned<Cursor> CreateCursor() const {
    FailureOrOwned<Cursor> bound_child(child()->CreateCursor());
    PROPAGATE_ON_FAILURE(bound_child);
    FailureOrOwned<BoundExpressionTree> bound_computation(
        computation_->Bind(bound_child->schema(),
                           buffer_allocator(),
                           default_row_count()));
    PROPAGATE_ON_FAILURE(bound_computation);
    return BoundCompute(bound_computation.release(), buffer_allocator(),
                        default_row_count(), bound_child.release());
  }

 private:
  const std::unique_ptr<const Expression> computation_;
};

}  // namespace

Operation* Compute(const Expression* computation, Operation* child) {
  return new ComputeOperation(computation, child);

}
FailureOrOwned<Cursor> BoundCompute(BoundExpressionTree* const computation,
                                    BufferAllocator* const allocator,
                                    const rowcount_t max_row_count,
                                    Cursor* const child) {
  return common::Success(new ComputeCursor(computation, max_row_count, child));
}

}  // namespace image
