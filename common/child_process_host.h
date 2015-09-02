// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMON_CHILD_PROCESS_HOST_H_
#define COMMON_CHILD_PROCESS_HOST_H_

#include "base/files/scoped_file.h"
#include "base/memory/shared_memory.h"
#include "build/build_config.h"
#include "ipc/ipc_channel_proxy.h"
//#include "ui/gfx/gpu_memory_buffer.h"

namespace base {
class FilePath;
}

namespace IPC {
class MessageFilter;
}

namespace common {
class ChildProcessHostDelegate;

// This represents a non-engine process. This can include traditional child
// processes that run independent of the engine process.
class ChildProcessHost : public IPC::Sender,
                         public IPC::Listener {
 public:

  static void AllocateSharedMemory(
      size_t buffer_size, base::ProcessHandle child_process,
      base::SharedMemoryHandle* handle);
  // Returns a unique ID to identify a child process. On construction, this
  // function will be used to generate the id_, but it is also used to generate
  // IDs for the RenderProcessHost, which doesn't inherit from us, and whose IDs
  // must be unique for all child processes.
  //
  // This function is threadsafe since RenderProcessHost is on the UI thread,
  // but normally this will be used on the IO thread.
  //
  // This will never return ChildProcessHost::kInvalidUniqueID.
  static int GenerateChildProcessUniqueId();

  ~ChildProcessHost() override;

  // This is a value never returned as the unique id of any child processes of
  // any kind, including the values returned by RenderProcessHost::GetID().
  static int kInvalidUniqueID;

  // Used to create a child process host. The delegate must outlive this object.
  static ChildProcessHost* Create(ChildProcessHostDelegate* delegate);

  // These flags may be passed to GetChildPath in order to alter its behavior,
  // causing it to return a child path more suited to a specific task.
  enum {
    // No special behavior requested.
    CHILD_NORMAL = 0,

#if defined(OS_LINUX)
    // Indicates that the child execed after forking may be execced from
    // /proc/self/exe rather than using the "real" app path. This prevents
    // autoupdate from confusing us if it changes the file out from under us.
    // You will generally want to set this on Linux, except when there is an
    // override to the command line (for example, we're forking a renderer in
    // gdb). In this case, you'd use GetChildPath to get the real executable
    // file name, and then prepend the GDB command to the command line.
    CHILD_ALLOW_SELF = 1 << 0,
#elif defined(OS_MACOSX)

    // Requests that the child run in a process that does not have the
    // PIE (position-independent executable) bit set, effectively disabling
    // ASLR. For process types that need to allocate a large contiguous
    // region, ASLR may not leave a large enough "hole" for the purpose. This
    // option should be used sparingly, and only when absolutely necessary.
    // This option is currently incompatible with CHILD_ALLOW_HEAP_EXECUTION.
    CHILD_NO_PIE = 1 << 1,

    // Requests that the child run in a process that does not protect the
    // heap against execution. Normally, heap pages may be made executable
    // with mprotect, so this mode should be used sparingly. It is intended
    // for processes that may host plug-ins that expect an executable heap
    // without having to call mprotect. This option is currently incompatible
    // with CHILD_NO_PIE.
    CHILD_ALLOW_HEAP_EXECUTION = 1 << 2,
#endif
  };

  // Returns the pathname to be used for a child process.  If a subprocess
  // pathname was specified on the command line, that will be used.  Otherwise,
  // the default child process pathname will be returned.  On most platforms,
  // this will be the same as the currently-executing process.
  //
  // The |flags| argument accepts one or more flags such as CHILD_ALLOW_SELF
  // and CHILD_ALLOW_HEAP_EXECUTION as defined above. Pass only CHILD_NORMAL
  // if none of these special behaviors are required.
  //
  // On failure, returns an empty FilePath.
  static base::FilePath GetChildPath(int flags);

  // Send the shutdown message to the child process.
  // Does not check with the delegate's CanShutdown.
  void ForceShutdown();

  // Creates the IPC channel.  Returns the channel id if it succeeded, an
  // empty string otherwise
  std::string CreateChannel();

  // Returns true iff the IPC channel is currently being opened;
  bool IsChannelOpening();

  // Adds an IPC message filter.  A reference will be kept to the filter.
  void AddFilter(IPC::MessageFilter* filter);

#if defined(OS_POSIX)
  // See IPC::Channel::TakeClientFileDescriptor.
  base::ScopedFD TakeClientFileDescriptor();
#endif

  bool Send(IPC::Message* message) override;

private:
  ChildProcessHost(ChildProcessHostDelegate* delegate);

  // IPC::Listener methods:
  bool OnMessageReceived(const IPC::Message& msg) override;
  void OnChannelConnected(int32 peer_pid) override;
  void OnChannelError() override;
  void OnBadMessageReceived(const IPC::Message& message) override;
 
  // Message handlers:
  void OnShutdownRequest();
 /* void OnAllocateSharedMemory(uint32 buffer_size,
                              base::SharedMemoryHandle* handle);
  void OnAllocateGpuMemoryBuffer(
   uint32 width,
   uint32 height,
   gfx::GpuMemoryBuffer::Format format,
   gfx::GpuMemoryBuffer::Usage usage,
   gfx::GpuMemoryBufferHandle* handle);

  void OnDeletedGpuMemoryBuffer(
   gfx::GpuMemoryBufferId id,
   uint32 sync_point);*/

  ChildProcessHostDelegate* delegate_;
  base::Process peer_process_;
  bool opening_channel_;  // True while we're waiting the channel to be opened.
  scoped_ptr<IPC::Channel> channel_;
  std::string channel_id_;

  // Holds all the IPC message filters.  Since this object lives on the IO
  // thread, we don't have a IPC::ChannelProxy and so we manage filters
  // manually.
  std::vector<scoped_refptr<IPC::MessageFilter> > filters_;

  DISALLOW_COPY_AND_ASSIGN(ChildProcessHost);
};

};  // namespace stripes

#endif  // COMMON_CHILD_PROCESS_HOST_H_
