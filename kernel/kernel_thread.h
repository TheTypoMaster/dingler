// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KERNEL_THREAD_H__
#define KERNEL_THREAD_H__

#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/location.h"
#include "base/logging.h"
#include "base/single_thread_task_runner.h"
#include "base/task_runner_util.h"
#include "base/time/time.h"
#include "base/threading/thread.h"

namespace base {
class MessageLoop;
class SequencedWorkerPool;
class Thread;
}

namespace kernel {
class KernelThreadDelegate;

// Use DCHECK_CURRENTLY_ON(BrowserThread::ID) to assert that a function can only
// be called on the named BrowserThread.
#define DCHECK_CURRENTLY_ON(thread_identifier)                      \
  (DCHECK(::kernel::KernelThread::CurrentlyOn(thread_identifier)) \
   << ::kernel::KernelThread::GetDCheckCurrentlyOnErrorMessage(   \
          thread_identifier))

///////////////////////////////////////////////////////////////////////////////
// KernelThread
//
// Utility functions for threads that are known by a browser-wide
// name.  For example, there is one IO thread for the entire browser
// process, and various pieces of code find it useful to retrieve a
// pointer to the IO thread's message loop.
//
// Invoke a task by thread ID:
//
//   KernelThread::PostTask(BrowserThread::IO, FROM_HERE, task);
//
// The return value is false if the task couldn't be posted because the target
// thread doesn't exist.  If this could lead to data loss, you need to check the
// result and restructure the code to ensure it doesn't occur.
//
// This class automatically handles the lifetime of different threads.
// It's always safe to call PostTask on any thread.  If it's not yet created,
// the task is deleted.  There are no race conditions.  If the thread that the
// task is posted to is guaranteed to outlive the current thread, then no locks
// are used.  You should never need to cache pointers to MessageLoops, since
// they're not thread safe.

class KernelThread : public base::Thread {
public:
 
 enum ID {
  MAIN,
  IO,
  FILE,
  CONTAINER,
  PROCESS_LAUNCHER,
  MAX
 };

 // Construct a BrowserThreadImpl with the supplied identifier.  It is an error
 // to construct a BrowserThreadImpl that already exists.
 explicit KernelThread(ID identifier);

 // Special constructor for the main thread and unittests. If a
 // |message_loop| is provied, we use a dummy thread here since the main
 // thread already exists.
 KernelThread(ID identifier,
  base::MessageLoop* message_loop);
 
 virtual ~KernelThread();

 bool StartWithOptions(const Options& options);

 static void ShutdownThreadPool();

 // These are the same methods in message_loop.h, but are guaranteed to either
 // get posted to the MessageLoop if it's still alive, or be deleted otherwise.
 // They return true iff the thread existed and the task was posted.  Note that
 // even if the task is posted, there's no guarantee that it will run, since
 // the target thread may already have a Quit message in its queue.

 static bool PostTask(ID identifier,
  const tracked_objects::Location& from_here,
  const base::Closure& task);

 static bool PostDelayedTask(ID identifier,
  const tracked_objects::Location& from_here,
  const base::Closure& task,
  base::TimeDelta delay);

 static bool PostNonNestableTask(ID identifier,
  const tracked_objects::Location& from_here,
  const base::Closure& task);

 static bool PostNonNestableDelayedTask(
  ID identifier,
  const tracked_objects::Location& from_here,
  const base::Closure& task,
  base::TimeDelta delay);

 static bool PostTaskAndReply(
  ID identifier,
  const tracked_objects::Location& from_here,
  const base::Closure& task,
  const base::Closure& reply);

 template <typename ReturnType, typename ReplyArgType>
 static bool PostTaskAndReplyWithResult(
  ID identifier,
  const tracked_objects::Location& from_here,
  const base::Callback<ReturnType(void)>& task,
  const base::Callback<void(ReplyArgType)>& reply) {
  scoped_refptr<base::SingleThreadTaskRunner> task_runner =
   GetMessageLoopProxyForThread(identifier);
  return base::PostTaskAndReplyWithResult(task_runner.get(), from_here, task,
   reply);
 }

 template <class T>
 static bool DeleteSoon(ID identifier,
  const tracked_objects::Location& from_here,
  const T* object) {
  return GetMessageLoopProxyForThread(identifier)->DeleteSoon(
   from_here, object);
 }

 template <class T>
 static bool ReleaseSoon(ID identifier,
  const tracked_objects::Location& from_here,
  const T* object) {
  return GetMessageLoopProxyForThread(identifier)->ReleaseSoon(
   from_here, object);
 }

 // Simplified wrappers for posting to the blocking thread pool. Use this
 // for doing things like blocking I/O.
 //
 // The first variant will run the task in the pool with no sequencing
 // semantics, so may get run in parallel with other posted tasks. The second
 // variant will all post a task with no sequencing semantics, and will post a
 // reply task to the origin TaskRunner upon completion.  The third variant
 // provides sequencing between tasks with the same sequence token name.
 //
 // These tasks are guaranteed to run before shutdown.
 //
 // If you need to provide different shutdown semantics (like you have
 // something slow and noncritical that doesn't need to block shutdown),
 // or you want to manually provide a sequence token (which saves a map
 // lookup and is guaranteed unique without you having to come up with a
 // unique string), you can access the sequenced worker pool directly via
 // GetBlockingPool().
 //
 // If you need to PostTaskAndReplyWithResult, use
 // base::PostTaskAndReplyWithResult() with GetBlockingPool() as the task
 // runner.

 static bool PostBlockingPoolTask(const tracked_objects::Location& from_here,
  const base::Closure& task);

 static bool PostBlockingPoolTaskAndReply(
  const tracked_objects::Location& from_here,
  const base::Closure& task,
  const base::Closure& reply);

 static bool PostBlockingPoolSequencedTask(
  const std::string& sequence_token_name,
  const tracked_objects::Location& from_here,
  const base::Closure& task);

 // For use with scheduling non-critical tasks for execution after startup.
 // The order or execution of tasks posted here is unspecified even when
 // posting to a SequencedTaskRunner and tasks are not guaranteed to be run
 // prior to browser shutdown.
 // Note: see related ContentBrowserClient::PostAfterStartupTask.

 static void PostAfterStartupTask(
  const tracked_objects::Location& from_here,
  const scoped_refptr<base::TaskRunner>& task_runner,
  const base::Closure& task);

 // Returns the thread pool used for blocking file I/O. Use this object to
 // perform random blocking operations such as file writes or querying the
 // Windows registry.
 static base::SequencedWorkerPool* GetBlockingPool() WARN_UNUSED_RESULT;

 // Callable on any thread.  Returns whether the given well-known thread is
 // initialized.
 static bool IsThreadInitialized(ID identifier) WARN_UNUSED_RESULT;

 // Callable on any thread.  Returns whether you're currently on a particular
 // thread.  To DCHECK this, use the DCHECK_CURRENTLY_ON() macro above.
 static bool CurrentlyOn(ID identifier) WARN_UNUSED_RESULT;

 // Callable on any thread.  Returns whether the threads message loop is valid.
 // If this returns false it means the thread is in the process of shutting
 // down.
 static bool IsMessageLoopValid(ID identifier) WARN_UNUSED_RESULT;

 // If the current message loop is one of the known threads, returns true and
 // sets identifier to its ID.  Otherwise returns false.
 static bool GetCurrentThreadIdentifier(ID* identifier) WARN_UNUSED_RESULT;

 // Callers can hold on to a refcounted task runner beyond the lifetime
 // of the thread.
 static scoped_refptr<base::SingleThreadTaskRunner>
  GetMessageLoopProxyForThread(ID identifier);

 // Returns a pointer to the thread's message loop, which will become
 // invalid during shutdown, so you probably shouldn't hold onto it.
 //
 // This must not be called before the thread is started, or after
 // the thread is stopped, or it will DCHECK.
 //
 // Ownership remains with the BrowserThread implementation, so you
 // must not delete the pointer.
 static base::MessageLoop* UnsafeGetMessageLoopForThread(ID identifier);

 // Sets the delegate for the specified BrowserThread.
 //
 // Only one delegate may be registered at a time.  Delegates may be
 // unregistered by providing a nullptr pointer.
 //
 // If the caller unregisters a delegate before CleanUp has been
 // called, it must perform its own locking to ensure the delegate is
 // not deleted while unregistering.
 static void SetDelegate(ID identifier, KernelThreadDelegate* delegate);

 // Use these templates in conjunction with RefCountedThreadSafe or scoped_ptr
 // when you want to ensure that an object is deleted on a specific thread.
 // This is needed when an object can hop between threads
 // (i.e. IO -> FILE -> IO), and thread switching delays can mean that the
 // final IO tasks executes before the FILE task's stack unwinds.
 // This would lead to the object destructing on the FILE thread, which often
 // is not what you want (i.e. to unregister from NotificationService, to
 // notify other objects on the creating thread etc).

 template<ID thread>
 struct DeleteOnThread {
  template<typename T>
  static void Destruct(const T* x) {
   if (CurrentlyOn(thread)) {
    delete x;
   }
   else {
    if (!DeleteSoon(thread, FROM_HERE, x)) {
#if defined(UNIT_TEST)
     // Only logged under unit testing because leaks at shutdown
     // are acceptable under normal circumstances.
     LOG(ERROR) << "DeleteSoon failed on thread " << thread;
#endif  // UNIT_TEST
    }
   }
  }
  template <typename T>
  inline void operator()(T* ptr) const {
   enum { type_must_be_complete = sizeof(T) };
   Destruct(ptr);
  }
 };

 // Sample usage with RefCountedThreadSafe:
 // class Foo
 //     : public base::RefCountedThreadSafe<
 //           Foo, BrowserThread::DeleteOnIOThread> {
 //
 // ...
 //  private:
 //   friend struct BrowserThread::DeleteOnThread<BrowserThread::IO>;
 //   friend class base::DeleteHelper<Foo>;
 //
 //   ~Foo();
 //
 // Sample usage with scoped_ptr:
 // scoped_ptr<Foo, BrowserThread::DeleteOnIOThread> ptr;

 struct DeleteOnMainThread : public DeleteOnThread<MAIN> { };
 struct DeleteOnIOThread : public DeleteOnThread<IO> { };
 struct DeleteOnFileThread : public DeleteOnThread<FILE> { };
 struct DeleteOnContainerThread : public DeleteOnThread<CONTAINER> { };
 struct DeleteOnProcessLauncherThread : public DeleteOnThread<PROCESS_LAUNCHER>{};
 
 // Returns an appropriate error message for when DCHECK_CURRENTLY_ON() fails.
 static std::string GetDCheckCurrentlyOnErrorMessage(ID expected);

protected:

 void Init() override;
 void Run(base::MessageLoop* message_loop) override;
 void CleanUp() override;

private:

 // The following are unique function names that makes it possible to tell
 // the thread id from the callstack alone in crash dumps.
 void MainThreadRun(base::MessageLoop* message_loop);
 void FileThreadRun(base::MessageLoop* message_loop);
 void ContainerThreadRun(base::MessageLoop* message_loop);
 void IOThreadRun(base::MessageLoop* message_loop);
 void ProcessLauncherThreadRun(base::MessageLoop* message_loop);

 static bool PostTaskHelper(
  KernelThread::ID identifier,
  const tracked_objects::Location& from_here,
  const base::Closure& task,
  base::TimeDelta delay,
  bool nestable);

 // Common initialization code for the constructors.
 void Initialize();

 ID identifier_;
 
 DISALLOW_COPY_AND_ASSIGN(KernelThread);
};

}

#endif
