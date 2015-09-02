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

#include "image/query/cursor/benchmarks.h"

#include <memory>
#include <string>

#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/stringprintf.h"
#include "image/query/utils/macros.h"
#include "image/query/utils/failureor.h"
#include "image/query/base/exception.h"
#include "image/query/base/exception_macros.h"
#include "image/query/base/block.h"
#include "image/query/base/types.h"
#include "image/query/cursor/cursor.h"
#include "image/query/cursor/cursors.pb.h"
#include "image/query/cursor/cursor_transformer.h"

namespace image {

class TupleSchema;

class BenchmarkedCursor : public Cursor {
 public:
  explicit BenchmarkedCursor(OperationBenchmarkListener* benchmark_listener)
      : benchmark_listener_(benchmark_listener),
        num_rows_generated_(0),
        benchmark_done_(true) {
    CHECK(benchmark_listener);
  }

  virtual ~BenchmarkedCursor() {
    StopBenchmark();
  }

  virtual const TupleSchema& schema() const {
    return cursor_->schema();
  }

  // Creates a cursor and measures the time spent creating it.
  FailureOrVoid Create(Operation* operation) {
    benchmark_done_ = false;
    time_measurer_.Start();
    benchmark_listener_->OnBenchmarkStarted(time_measurer_.start_time());
    FailureOrOwned<Cursor> result = operation->CreateCursor();
    if (result.is_failure()) {
      benchmark_done_ = true;
      time_measurer_.Stop();
      PROPAGATE_ON_FAILURE(result);
    }
    time_measurer_.Pause();
    benchmark_listener_->OnCreateFinished(time_measurer_.GetSystemTime());
    cursor_.reset(result.release());
    return common::Success();
  }

  virtual ResultView Next(rowcount_t max_row_count) {
    DCHECK(cursor_.get() != NULL);
    time_measurer_.Resume();
    ResultView result = cursor_->Next(max_row_count);
    if (result.has_data()) {
      num_rows_generated_ += result.view().row_count();
      time_measurer_.Pause();
    } else {
      StopBenchmark();
    }
    return result;
  }

  virtual void Interrupt() { cursor_->Interrupt(); }

  virtual void ApplyToChildren(CursorTransformer* transformer) {
    cursor_->ApplyToChildren(transformer);
  }

  virtual CursorId GetCursorId() const { return BENCHMARK; }

  virtual void AppendDebugDescription(string* target) const {
    target->append("Benchmarked(");
    cursor_->AppendDebugDescription(target);
    target->append(")");
  }

 private:
  void StopBenchmark() {
    if (benchmark_done_) {
      return;
    }
    benchmark_done_ = true;
    // Stop time measurement.
    time_measurer_.Stop();
    float paused_percentage =
      time_measurer_.paused_time() * 100.0
      / (time_measurer_.active_wall_time() + time_measurer_.paused_time());
    VLOG(1) << base::StringPrintf(
        "BenchmarkedCursor was paused %.2f%% of total time.",
        paused_percentage);
    benchmark_listener_->OnBenchmarkFinished(
        time_measurer_.stop_time(),
        num_rows_generated_,
        time_measurer_.active_wall_time(),
        time_measurer_.paused_time(),
        time_measurer_.active_user_time(),
        time_measurer_.active_system_time());
  }

  std::unique_ptr<Cursor> cursor_;
  OperationBenchmarkListener* benchmark_listener_;
  rowcount_t num_rows_generated_;
  Timer<true> time_measurer_;
  bool benchmark_done_;
  DISALLOW_COPY_AND_ASSIGN(BenchmarkedCursor);
};

FailureOrOwned<Cursor> BenchmarkedOperation::CreateCursor() const {
  std::unique_ptr<BenchmarkedCursor> benchmarked_cursor(
      new BenchmarkedCursor(benchmark_listener_));
  PROPAGATE_ON_FAILURE(benchmarked_cursor->Create(operation_.get()));
  return common::Success(benchmarked_cursor.release());
}

}  // namespace image
