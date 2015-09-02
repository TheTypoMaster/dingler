// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "kernel/kernel_thread.h"

#include <string>
#include "base/atomicops.h"
#include "base/bind.h"
#include "base/compiler_specific.h"
#include "base/lazy_instance.h"
#include "base/single_thread_task_runner.h"
#include "base/threading/sequenced_worker_pool.h"
#include "base/threading/thread_restrictions.h"
#include "common/client.h"
#include "kernel/kernel_thread_delegate.h"
#include "kernel/kernel_client.h"
#include "net/disk_cache/simple/simple_backend_impl.h"
#if defined(OS_ANDROID)
#include "base/android/jni_android.h"
#endif

namespace kernel {
 
namespace {
 // Friendly names for the well-known threads.
 static const char* g_kernel_thread_names[KernelThread::MAX] = {
   "",  // MAIN (name assembled in kernel_main.cc).
   "Kernel_FileThread",  // FILE
   "Kernel_ContainerThread",  // CONTAINER
   "Kernel_IOThread",  // IO
   "Kernel_ProcessLauncherThread",  // IO
  };

 // An implementation of SingleThreadTaskRunner to be used in conjunction
 // with KernelThread.
 class KernelThreadTaskRunner : public base::SingleThreadTaskRunner {
 public:
  explicit KernelThreadTaskRunner(KernelThread::ID identifier)
    : id_(identifier) {}
  
  // SingleThreadTaskRunner implementation.
  bool PostDelayedTask(const tracked_objects::Location& from_here,
   const base::Closure& task,
   base::TimeDelta delay) override {
  
   return KernelThread::PostDelayedTask(id_, from_here, task, delay);
  
  }

  bool PostNonNestableDelayedTask(const tracked_objects::Location& from_here,
   const base::Closure& task,
   base::TimeDelta delay) override {
   
   return KernelThread::PostNonNestableDelayedTask(id_, from_here, task,
     delay);
  }

  bool RunsTasksOnCurrentThread() const override {
   return KernelThread::CurrentlyOn(id_);
  }

 protected:
  ~KernelThreadTaskRunner() override {}
 private:
  KernelThread::ID id_;
  
  DISALLOW_COPY_AND_ASSIGN(KernelThreadTaskRunner);
 };

 // A separate helper is used just for the task runners, in order to avoid
 // needing to initialize the globals to create a task runner.
 struct KernelThreadTaskRunners {
  KernelThreadTaskRunners() {
   for (int i = 0; i < KernelThread::MAX; ++i) {
     proxies[i] =
      new KernelThreadTaskRunner(static_cast<KernelThread::ID>(i));
   }
  }
  
  scoped_refptr<base::SingleThreadTaskRunner> proxies[KernelThread::MAX];
 };

 base::LazyInstance<KernelThreadTaskRunners>::Leaky g_task_runners =
   LAZY_INSTANCE_INITIALIZER;

 struct KernelThreadGlobals {
  KernelThreadGlobals()
    : blocking_pool(new base::SequencedWorkerPool(3, "KernelBlocking")) {
   memset(threads, 0, KernelThread::MAX * sizeof(threads[0]));
    memset(thread_delegates, 0,
     KernelThread::MAX * sizeof(thread_delegates[0]));
   }
   // This lock protects |threads|. Do not read or modify that array
   // without holding this lock. Do not block while holding this lock.
   base::Lock lock;
   // This array is protected by |lock|. The threads are not owned by this
   // array. Typically, the threads are owned on the UI thread by
   // BrowserMainLoop. KernelThread objects remove themselves from this
   // array upon destruction.
   KernelThread* threads[KernelThread::MAX];
   // Only atomic operations are used on this array. The delegates are not owned
   // by this array, rather by whoever calls KernelThread::SetDelegate.
   KernelThreadDelegate* thread_delegates[KernelThread::MAX];

   const scoped_refptr<base::SequencedWorkerPool> blocking_pool;
  };

 base::LazyInstance<KernelThreadGlobals>::Leaky
   g_globals = LAZY_INSTANCE_INITIALIZER;

}  // namespace

KernelThread::KernelThread(KernelThread::ID identifier)
 : Thread(g_kernel_thread_names[identifier]),
 identifier_(identifier) {
 
 Initialize();
}

KernelThread::KernelThread(ID identifier,
 base::MessageLoop* message_loop)
 : Thread(message_loop->thread_name()), identifier_(identifier) {
 set_message_loop(message_loop);
 Initialize();
}

// static
void KernelThread::ShutdownThreadPool() {
 // The goal is to make it impossible for dingler to 'infinite loop' during
 // shutdown, but to reasonably expect that all BLOCKING_SHUTDOWN tasks queued
 // during shutdown get run. There's nothing particularly scientific about the
 // number chosen.
 const int kMaxNewShutdownBlockingTasks = 1000;
 KernelThreadGlobals& globals = g_globals.Get();
 globals.blocking_pool->Shutdown(kMaxNewShutdownBlockingTasks);
}


void KernelThread::Init() {
 KernelThreadGlobals& globals = g_globals.Get();
 using base::subtle::AtomicWord;
 AtomicWord* storage =
  reinterpret_cast<AtomicWord*>(&globals.thread_delegates[identifier_]);
 AtomicWord stored_pointer = base::subtle::NoBarrier_Load(storage);
 KernelThreadDelegate* delegate =
  reinterpret_cast<KernelThreadDelegate*>(stored_pointer);
 if (delegate)
  delegate->Init();
}

// We disable optimizations for this block of functions so the compiler doesn't
// merge them all together.
MSVC_DISABLE_OPTIMIZE()
MSVC_PUSH_DISABLE_WARNING(4748)

NOINLINE void KernelThread::MainThreadRun(base::MessageLoop* message_loop) {
 volatile int line_number = __LINE__;
 Thread::Run(message_loop);
 CHECK_GT(line_number, 0);
}

NOINLINE void KernelThread::FileThreadRun(
 base::MessageLoop* message_loop) {
 volatile int line_number = __LINE__;
 Thread::Run(message_loop);
 CHECK_GT(line_number, 0);
}

NOINLINE void KernelThread::ContainerThreadRun(
 base::MessageLoop* message_loop) {
 volatile int line_number = __LINE__;
 Thread::Run(message_loop);
 CHECK_GT(line_number, 0);
}

NOINLINE void KernelThread::IOThreadRun(base::MessageLoop* message_loop) {
 volatile int line_number = __LINE__;
 Thread::Run(message_loop);
 CHECK_GT(line_number, 0);
}

NOINLINE void KernelThread::ProcessLauncherThreadRun(base::MessageLoop* message_loop) {
 volatile int line_number = __LINE__;
 Thread::Run(message_loop);
 CHECK_GT(line_number, 0);
}

MSVC_POP_WARNING()
MSVC_ENABLE_OPTIMIZE();

void KernelThread::Run(base::MessageLoop* message_loop) {
#if defined(OS_ANDROID)
 // Not to reset thread name to "Thread-???" by VM, attach VM with thread name.
 // Though it may create unnecessary VM thread objects, keeping thread name
 // gives more benefit in debugging in the platform.
 if (!thread_name().empty()) {
  base::android::AttachCurrentThreadWithName(thread_name());
 }
#endif
 KernelThread::ID thread_id = MAX;
 if (!GetCurrentThreadIdentifier(&thread_id))
  return Thread::Run(message_loop);
 switch (thread_id) {
 case KernelThread::MAIN:
  return MainThreadRun(message_loop);
 case KernelThread::FILE:
  return FileThreadRun(message_loop);
 case KernelThread::CONTAINER:
  return ContainerThreadRun(message_loop);
 case KernelThread::IO:
  return IOThreadRun(message_loop);
 case KernelThread::PROCESS_LAUNCHER:
  return ProcessLauncherThreadRun(message_loop);
 case KernelThread::MAX:
  CHECK(false);  // This shouldn't actually be reached!
  break;
 }
 Thread::Run(message_loop);
}

void KernelThread::CleanUp() {
 KernelThreadGlobals& globals = g_globals.Get();
 using base::subtle::AtomicWord;
 AtomicWord* storage =
  reinterpret_cast<AtomicWord*>(&globals.thread_delegates[identifier_]);
 AtomicWord stored_pointer = base::subtle::NoBarrier_Load(storage);
 KernelThreadDelegate* delegate =
  reinterpret_cast<KernelThreadDelegate*>(stored_pointer);
 if (delegate)
  delegate->CleanUp();
}

void KernelThread::Initialize() {
 KernelThreadGlobals& globals = g_globals.Get();
 base::AutoLock lock(globals.lock);
 DCHECK(identifier_ >= 0 && identifier_ < MAX);
 DCHECK(globals.threads[identifier_] == NULL);
 globals.threads[identifier_] = this;
}

KernelThread::~KernelThread() {
 // All Thread subclasses must call Stop() in the destructor. This is
 // doubly important here as various bits of code check they are on
 // the right KernelThread.
 Stop();
 KernelThreadGlobals& globals = g_globals.Get();
 base::AutoLock lock(globals.lock);
 globals.threads[identifier_] = NULL;
#ifndef NDEBUG
 // Double check that the threads are ordered correctly in the enumeration.
 for (int i = identifier_ + 1; i < MAX; ++i) {
  DCHECK(!globals.threads[i]) <<
   "Threads must be listed in the reverse order that they die";
 }
#endif
}

bool KernelThread::StartWithOptions(const Options& options) {
 // The global thread table needs to be locked while a new thread is
 // starting, as the new thread can asynchronously start touching the
 // table (and other thread's message_loop).
 KernelThreadGlobals& globals = g_globals.Get();
 base::AutoLock lock(globals.lock);
 return Thread::StartWithOptions(options);
}

// static
bool KernelThread::PostTaskHelper(
 KernelThread::ID identifier,
 const tracked_objects::Location& from_here,
 const base::Closure& task,
 base::TimeDelta delay,
 bool nestable) {
 DCHECK(identifier >= 0 && identifier < MAX);
 // Optimization: to avoid unnecessary locks, we listed the ID enumeration in
 // order of lifetime.  So no need to lock if we know that the target thread
 // outlives current thread.
 // Note: since the array is so small, ok to loop instead of creating a map,
 // which would require a lock because std::map isn't thread safe, defeating
 // the whole purpose of this optimization.
 KernelThread::ID current_thread = MAX;
 bool target_thread_outlives_current =
  GetCurrentThreadIdentifier(&current_thread) &&
  current_thread >= identifier;
 KernelThreadGlobals& globals = g_globals.Get();
 if (!target_thread_outlives_current)
  globals.lock.Acquire();
 base::MessageLoop* message_loop =
  globals.threads[identifier] ? globals.threads[identifier]->message_loop()
  : NULL;
 if (message_loop) {
  if (nestable) {
   message_loop->task_runner()->PostDelayedTask(from_here, task, delay);
  }
  else {
   message_loop->task_runner()->PostNonNestableDelayedTask(from_here, task,
    delay);
  }
 }
 if (!target_thread_outlives_current)
  globals.lock.Release();
 return !!message_loop;
}

// static
bool KernelThread::PostBlockingPoolTask(
 const tracked_objects::Location& from_here,
 const base::Closure& task) {
 return g_globals.Get().blocking_pool->PostWorkerTask(from_here, task);
}

// static
bool KernelThread::PostBlockingPoolTaskAndReply(
 const tracked_objects::Location& from_here,
 const base::Closure& task,
 const base::Closure& reply) {
 return g_globals.Get().blocking_pool->PostTaskAndReply(
  from_here, task, reply);
}

// static
bool KernelThread::PostBlockingPoolSequencedTask(
 const std::string& sequence_token_name,
 const tracked_objects::Location& from_here,
 const base::Closure& task) {
 return g_globals.Get().blocking_pool->PostNamedSequencedWorkerTask(
  sequence_token_name, from_here, task);
}

// static
void KernelThread::PostAfterStartupTask(
 const tracked_objects::Location& from_here,
 const scoped_refptr<base::TaskRunner>& task_runner,
 const base::Closure& task) {

 common::GetClient()->kernel()->PostAfterStartupTask(from_here, task_runner,
  task);
}

// static
base::SequencedWorkerPool* KernelThread::GetBlockingPool() {
 return g_globals.Get().blocking_pool.get();
}

// static
bool KernelThread::IsThreadInitialized(ID identifier) {
 if (g_globals == NULL)
  return false;
 KernelThreadGlobals& globals = g_globals.Get();
 base::AutoLock lock(globals.lock);
 DCHECK(identifier >= 0 && identifier < MAX);
 return globals.threads[identifier] != NULL;
}

// static
bool KernelThread::CurrentlyOn(ID identifier) {
 // We shouldn't use MessageLoop::current() since it uses LazyInstance which
 // may be deleted by ~AtExitManager when a WorkerPool thread calls this
 // function.
 // http://crbug.com/63678
 base::ThreadRestrictions::ScopedAllowSingleton allow_singleton;
 KernelThreadGlobals& globals = g_globals.Get();
 base::AutoLock lock(globals.lock);
 DCHECK(identifier >= 0 && identifier < MAX);
 return globals.threads[identifier] &&
  globals.threads[identifier]->message_loop() ==
  base::MessageLoop::current();
}

static const char* GetThreadName(KernelThread::ID thread) {
 if (KernelThread::MAIN < thread && thread < KernelThread::MAX)
  return g_kernel_thread_names[thread];
 if (thread == KernelThread::MAIN)
  return "Kernel_MainThread";
 return "Unknown Thread";
}

// static
std::string KernelThread::GetDCheckCurrentlyOnErrorMessage(ID expected) {
 const base::MessageLoop* message_loop = base::MessageLoop::current();
 ID actual_browser_thread;
 const char* actual_name = "Unknown Thread";
 if (message_loop && !message_loop->thread_name().empty()) {
  actual_name = message_loop->thread_name().c_str();
 }
 else if (GetCurrentThreadIdentifier(&actual_browser_thread)) {
  actual_name = GetThreadName(actual_browser_thread);
 }
 std::string result = "Must be called on ";
 result += GetThreadName(expected);
 result += "; actually called on ";
 result += actual_name;
 result += ".";
 return result;
}

// static
bool KernelThread::IsMessageLoopValid(ID identifier) {
 if (g_globals == NULL)
  return false;
 KernelThreadGlobals& globals = g_globals.Get();
 base::AutoLock lock(globals.lock);
 DCHECK(identifier >= 0 && identifier < MAX);
 return globals.threads[identifier] &&
  globals.threads[identifier]->message_loop();
}

// static
bool KernelThread::PostTask(ID identifier,
 const tracked_objects::Location& from_here,
 const base::Closure& task) {
 return KernelThread::PostTaskHelper(
  identifier, from_here, task, base::TimeDelta(), true);
}

// static
bool KernelThread::PostDelayedTask(ID identifier,
 const tracked_objects::Location& from_here,
 const base::Closure& task,
 base::TimeDelta delay) {
 return KernelThread::PostTaskHelper(
  identifier, from_here, task, delay, true);
}

// static
bool KernelThread::PostNonNestableTask(
 ID identifier,
 const tracked_objects::Location& from_here,
 const base::Closure& task) {
 return KernelThread::PostTaskHelper(
  identifier, from_here, task, base::TimeDelta(), false);
}

// static
bool KernelThread::PostNonNestableDelayedTask(
 ID identifier,
 const tracked_objects::Location& from_here,
 const base::Closure& task,
 base::TimeDelta delay) {
 return KernelThread::PostTaskHelper(
  identifier, from_here, task, delay, false);
}

// static
bool KernelThread::PostTaskAndReply(
 ID identifier,
 const tracked_objects::Location& from_here,
 const base::Closure& task,
 const base::Closure& reply) {
 return GetMessageLoopProxyForThread(identifier)->PostTaskAndReply(from_here,
  task,
  reply);
}

// static
bool KernelThread::GetCurrentThreadIdentifier(ID* identifier) {
 if (g_globals == NULL)
  return false;
 // We shouldn't use MessageLoop::current() since it uses LazyInstance which
 // may be deleted by ~AtExitManager when a WorkerPool thread calls this
 // function.
 // http://crbug.com/63678
 base::ThreadRestrictions::ScopedAllowSingleton allow_singleton;
 base::MessageLoop* cur_message_loop = base::MessageLoop::current();
 KernelThreadGlobals& globals = g_globals.Get();
 for (int i = 0; i < MAX; ++i) {
  if (globals.threads[i] &&
   globals.threads[i]->message_loop() == cur_message_loop) {
   *identifier = globals.threads[i]->identifier_;
   return true;
  }
 }
 return false;
}

// static
scoped_refptr<base::SingleThreadTaskRunner>
KernelThread::GetMessageLoopProxyForThread(ID identifier) {
 return g_task_runners.Get().proxies[identifier];
}

// static
base::MessageLoop* KernelThread::UnsafeGetMessageLoopForThread(ID identifier) {
 if (g_globals == NULL)
  return NULL;
 KernelThreadGlobals& globals = g_globals.Get();
 base::AutoLock lock(globals.lock);
 base::Thread* thread = globals.threads[identifier];
 DCHECK(thread);
 base::MessageLoop* loop = thread->message_loop();
 return loop;
}

// static
void KernelThread::SetDelegate(ID identifier,
 KernelThreadDelegate* delegate) {
 using base::subtle::AtomicWord;
 KernelThreadGlobals& globals = g_globals.Get();
 AtomicWord* storage = reinterpret_cast<AtomicWord*>(
  &globals.thread_delegates[identifier]);
 AtomicWord old_pointer = base::subtle::NoBarrier_AtomicExchange(
  storage, reinterpret_cast<AtomicWord>(delegate));
 // This catches registration when previously registered.
 DCHECK(!delegate || !old_pointer);
}


}