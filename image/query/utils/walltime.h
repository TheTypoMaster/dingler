// Copyright 2012 Google Inc. All Rights Reserved.
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
// The file provides walltime functionalities for the open source version
// of Supersonic.
#ifndef IMAGE_OPENSOURCE_TIMER_WALLTIME_H_
#define IMAGE_OPENSOURCE_TIMER_WALLTIME_H_

//#include <sys/time.h>
#include <time.h>
#include <string>

#include "base/basictypes.h"
#include "build/build_config.h"

#if defined(OS_WIN)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
//#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#endif
#include "base/time/time.h"
#include "base/basictypes.h"
#include "base/macros.h"
#include "base/cpu.h"
#include "base/logging.h"
#include "base/numerics/safe_math.h"
#include "image/query/utils/casts.h"

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

// Time conversion utilities.
static const int64 kNumMillisPerSecond = 1000LL;

static const int64 kNumMicrosPerMilli = 1000LL;
static const int64 kNumMicrosPerSecond = kNumMicrosPerMilli * 1000LL;

typedef double WallTime;

// Append result to a supplied string.
// If an error occurs during conversion 'dst' is not modified.
void StringAppendStrftime(std::string* dst,
                          const char* format,
                          time_t when,
                          bool local);

// Similar to the WallTime_Parse, but it takes a boolean flag local as
// argument specifying if the time_spec is in local time or UTC
// time. If local is set to true, the same exact result as
// WallTime_Parse is returned.
//bool WallTime_Parse_Timezone(const char* time_spec,
//                             const char* format,
//                             const struct tm* default_time,
//                             bool local,
//                             WallTime* result);

// Return current time in seconds as a WallTime.
WallTime WallTime_Now();

typedef int64 MicrosecondsInt64;

// Returns the time since the Epoch measured in microseconds.
inline MicrosecondsInt64 GetCurrentTimeMicros() {
#if !defined(OS_WIN)
 timespec ts;
#ifdef __MACH__  // OS X does not have clock_gettime, use clock_get_time
  clock_serv_t cclock;
  mach_timespec_t mts;
  host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
  clock_get_time(cclock, &mts);
  mach_port_deallocate(mach_task_self(), cclock);
  ts.tv_sec = mts.tv_sec;
  ts.tv_nsec = mts.tv_nsec;
#else
  clock_gettime(CLOCK_REALTIME, &ts);
#endif
  return ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
#else

 FILETIME ft;
 ::GetSystemTimeAsFileTime(&ft);
 return (bit_cast<int64_t, FILETIME>(ft)) / 10;
#endif
}

// Returns the number of days from epoch that elapsed until the specified date.
// The date must be in year-month-day format. Returns -1 when the date argument
// is invalid.
//int32 GetDaysSinceEpoch(const char* date);

// A CycleClock yields the value of a cycle counter that increments at a rate
// that is approximately constant.
class CycleClock {
 public:
  // Return the value of the counter.
  static inline int64 Now();

 private:
  CycleClock();
};

#include "image/query/utils/cycleclock-inl.h"  // inline method bodies
#endif  // IMAGE_OPENSOURCE_TIMER_WALLTIME_H_
