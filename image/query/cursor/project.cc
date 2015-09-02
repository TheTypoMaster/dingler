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

#include "image/query/cursor/project.h"

#include <memory>

#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "image/query/utils/failureor.h"
#include "image/query/base/exception.h"
#include "image/query/base/exception_macros.h"
#include "image/query/base/result.h"
#include "image/query/base/block.h"
#include "image/query/base/projector.h"
#include "image/query/base/types.h"
#include "image/query/cursor/cursor.h"
#include "image/query/cursor/cursors.pb.h"
#include "image/query/cursor/operation.h"
#include "image/query/cursor/basic_cursor.h"
#include "image/query/cursor/basic_operation.h"

namespace image {

namespace {

class ProjectCursor : public BasicCursor {
 public:
  // Takes ownership of BoundSingleSourceProjector and child cursor.
  ProjectCursor(const BoundSingleSourceProjector* projector, Cursor* child)
      : BasicCursor(projector->result_schema(), child),
        projector_(projector),
        result_view_(projector->result_schema()) {}

  virtual ResultView Next(rowcount_t max_row_count) {
    ResultView next_result = child()->Next(max_row_count);
    PROPAGATE_ON_FAILURE(next_result);
    if (!next_result.has_data()) {
      CHECK(next_result.is_eos() || next_result.is_waiting_on_barrier());
      return next_result;
    }
    projector_->Project(next_result.view(), &result_view_);
    result_view_.set_row_count(next_result.view().row_count());
    return ResultView::Success(&result_view_);
  }

  virtual bool IsWaitingOnBarrierSupported() const { return true; }

  virtual CursorId GetCursorId() const { return PROJECT; }

 private:
  std::unique_ptr<const BoundSingleSourceProjector> projector_;
  View result_view_;

  DISALLOW_COPY_AND_ASSIGN(ProjectCursor);
};

class ProjectOperation : public BasicOperation {
 public:
  // Takes ownership of projector and child_operation.
  ProjectOperation(const SingleSourceProjector* projector,
                      Operation* child_operation)
      : BasicOperation(child_operation),
        projector_(projector) {}

  virtual ~ProjectOperation() {}

  virtual FailureOrOwned<Cursor> CreateCursor() const {
    FailureOrOwned<Cursor> child_cursor = child()->CreateCursor();
    PROPAGATE_ON_FAILURE(child_cursor);
    FailureOrOwned<const BoundSingleSourceProjector> bound_projector =
        projector_->Bind(child_cursor->schema());
    PROPAGATE_ON_FAILURE(bound_projector);
    return common::Success(
        BoundProject(bound_projector.release(), child_cursor.release()));
  }

 private:
  std::unique_ptr<const SingleSourceProjector> projector_;

  DISALLOW_COPY_AND_ASSIGN(ProjectOperation);
};

}  // namespace

Operation* Project(const SingleSourceProjector* projector,
                   Operation* child) {
  return new ProjectOperation(projector, child);
}

Cursor* BoundProject(const BoundSingleSourceProjector* projector,
                     Cursor* child) {
  return new ProjectCursor(projector, child);
}

}  // namespace image
