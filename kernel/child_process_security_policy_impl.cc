// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "kernel/child_process_security_policy_impl.h"

#include "base/command_line.h"
#include "base/files/file_path.h"
#include "base/logging.h"
#include "base/metrics/histogram.h"
#include "base/stl_util.h"
#include "base/strings/string_util.h"
//#include "kernel/site_instance_impl.h"
#include "kernel/child_process_data.h"
//#include "kernel/content_browser_client.h"
//#include "kernel/render_process_host.h"
//#include "common/bindings_policy.h"
#include "common/switches.h"
//#include "common/url_constants.h"
#include "net/base/filename_util.h"
#include "net/url_request/url_request.h"
//#include "storage/browser/fileapi/file_permission_policy.h"
//#include "storage/browser/fileapi/file_system_url.h"
//#include "storage/browser/fileapi/isolated_context.h"
//#include "storage/common/fileapi/file_system_util.h"
#include "url/gurl.h"

namespace kernel {

namespace {

// Used internally only. These bit positions have no relationship to any
// underlying OS and can be changed to accommodate finer-grained permissions.
enum ChildProcessSecurityPermissions {
  READ_FILE_PERMISSION             = 1 << 0,
  WRITE_FILE_PERMISSION            = 1 << 1,
  CREATE_NEW_FILE_PERMISSION       = 1 << 2,
  CREATE_OVERWRITE_FILE_PERMISSION = 1 << 3,
  DELETE_FILE_PERMISSION           = 1 << 4,

  // Used by Media Galleries API
  COPY_INTO_FILE_PERMISSION        = 1 << 5,
};

// Used internally only. Bitmasks that are actually used by the Grant* and Can*
// methods. These contain one or more ChildProcessSecurityPermissions.
enum ChildProcessSecurityGrants {
  READ_FILE_GRANT              = READ_FILE_PERMISSION,
  WRITE_FILE_GRANT             = WRITE_FILE_PERMISSION,

  CREATE_NEW_FILE_GRANT        = CREATE_NEW_FILE_PERMISSION |
                                 COPY_INTO_FILE_PERMISSION,

  CREATE_READ_WRITE_FILE_GRANT = CREATE_NEW_FILE_PERMISSION |
                                 CREATE_OVERWRITE_FILE_PERMISSION |
                                 READ_FILE_PERMISSION |
                                 WRITE_FILE_PERMISSION |
                                 COPY_INTO_FILE_PERMISSION |
                                 DELETE_FILE_PERMISSION,

  COPY_INTO_FILE_GRANT         = COPY_INTO_FILE_PERMISSION,
  DELETE_FILE_GRANT            = DELETE_FILE_PERMISSION,
};

}  // namespace

// The SecurityState class is used to maintain per-child process security state
// information.
class ChildProcessSecurityPolicyImpl::SecurityState {
 public:
  SecurityState()
    : enabled_bindings_(0),
      can_read_raw_cookies_(false),
      can_send_midi_sysex_(false) { }

  ~SecurityState() {
    scheme_policy_.clear();
   /* storage::IsolatedContext* isolated_context =
        storage::IsolatedContext::GetInstance();
    for (FileSystemMap::iterator iter = filesystem_permissions_.begin();
         iter != filesystem_permissions_.end();
         ++iter) {
      isolated_context->RemoveReference(iter->first);
    }
    UMA_HISTOGRAM_COUNTS("ChildProcessSecurityPolicy.PerChildFilePermissions",
                         file_permissions_.size());*/
  }

  // Grant permission to request URLs with the specified scheme.
  void GrantScheme(const std::string& scheme) {
    scheme_policy_[scheme] = true;
  }

  // Revoke permission to request URLs with the specified scheme.
  void RevokeScheme(const std::string& scheme) {
    scheme_policy_[scheme] = false;
  }

  // Grant certain permissions to a file.
  void GrantPermissionsForFile(const base::FilePath& file, int permissions) {
    base::FilePath stripped = file.StripTrailingSeparators();
    file_permissions_[stripped] |= permissions;
    UMA_HISTOGRAM_COUNTS("ChildProcessSecurityPolicy.FilePermissionPathLength",
                         stripped.value().size());
  }

  // Grant navigation to a file but not the file:// scheme in general.
  void GrantRequestOfSpecificFile(const base::FilePath &file) {
    request_file_set_.insert(file.StripTrailingSeparators());
  }

  // Revokes all permissions granted to a file.
  void RevokeAllPermissionsForFile(const base::FilePath& file) {
    base::FilePath stripped = file.StripTrailingSeparators();
    file_permissions_.erase(stripped);
    request_file_set_.erase(stripped);
  }

  // Grant certain permissions to a file.
  void GrantPermissionsForFileSystem(const std::string& filesystem_id,
                                     int permissions) {
    /*if (!ContainsKey(filesystem_permissions_, filesystem_id))
      storage::IsolatedContext::GetInstance()->AddReference(filesystem_id);*/
    filesystem_permissions_[filesystem_id] |= permissions;
  }

  bool HasPermissionsForFileSystem(const std::string& filesystem_id,
                                   int permissions) {
    FileSystemMap::const_iterator it =
        filesystem_permissions_.find(filesystem_id);
    if (it == filesystem_permissions_.end())
      return false;
    return (it->second & permissions) == permissions;
  }

#if defined(OS_ANDROID)
  // Determine if the certain permissions have been granted to a content URI.
  bool HasPermissionsForContentUri(const base::FilePath& file,
                                   int permissions) {
    DCHECK(!file.empty());
    DCHECK(file.IsContentUri());
    if (!permissions)
      return false;
    base::FilePath file_path = file.StripTrailingSeparators();
    FileMap::const_iterator it = file_permissions_.find(file_path);
    if (it != file_permissions_.end())
      return (it->second & permissions) == permissions;
    return false;
  }
#endif

  void GrantBindings(int bindings) {
    enabled_bindings_ |= bindings;
  }

  void GrantReadRawCookies() {
    can_read_raw_cookies_ = true;
  }

  void RevokeReadRawCookies() {
    can_read_raw_cookies_ = false;
  }

  void GrantPermissionForMidiSysEx() {
    can_send_midi_sysex_ = true;
  }

  // Determine whether permission has been granted to request |url|.
  bool CanRequestURL(const GURL& url) {
    // Having permission to a scheme implies permssion to all of its URLs.
    SchemeMap::const_iterator judgment(scheme_policy_.find(url.scheme()));
    if (judgment != scheme_policy_.end())
      return judgment->second;

    // file:// URLs are more granular.  The child may have been given
    // permission to a specific file but not the file:// scheme in general.
    if (url.SchemeIs(url::kFileScheme)) {
      base::FilePath path;
      if (net::FileURLToFilePath(url, &path))
        return ContainsKey(request_file_set_, path);
    }

    return false;  // Unmentioned schemes are disallowed.
  }

  // Determine if the certain permissions have been granted to a file.
  bool HasPermissionsForFile(const base::FilePath& file, int permissions) {
#if defined(OS_ANDROID)
    if (file.IsContentUri())
      return HasPermissionsForContentUri(file, permissions);
#endif
    if (!permissions || file.empty() || !file.IsAbsolute())
      return false;
    base::FilePath current_path = file.StripTrailingSeparators();
    base::FilePath last_path;
    int skip = 0;
    while (current_path != last_path) {
      base::FilePath base_name = current_path.BaseName();
      if (base_name.value() == base::FilePath::kParentDirectory) {
        ++skip;
      } else if (skip > 0) {
        if (base_name.value() != base::FilePath::kCurrentDirectory)
          --skip;
      } else {
        FileMap::const_iterator it = file_permissions_.find(current_path);
        if (it != file_permissions_.end())
          return (it->second & permissions) == permissions;
      }
      last_path = current_path;
      current_path = current_path.DirName();
    }

    return false;
  }

  void LockToOrigin(const GURL& gurl) {
    origin_lock_ = gurl;
  }

  //bool has_web_ui_bindings() const {
  //  return enabled_bindings_ & BINDINGS_POLICY_WEB_UI;
  //}

  bool can_read_raw_cookies() const {
    return can_read_raw_cookies_;
  }

  bool can_send_midi_sysex() const {
    return can_send_midi_sysex_;
  }

 private:
  typedef std::map<std::string, bool> SchemeMap;

  typedef int FilePermissionFlags;  // bit-set of base::File::Flags
  typedef std::map<base::FilePath, FilePermissionFlags> FileMap;
  typedef std::map<std::string, FilePermissionFlags> FileSystemMap;
  typedef std::set<base::FilePath> FileSet;

  // Maps URL schemes to whether permission has been granted or revoked:
  //   |true| means the scheme has been granted.
  //   |false| means the scheme has been revoked.
  // If a scheme is not present in the map, then it has never been granted
  // or revoked.
  SchemeMap scheme_policy_;

  // The set of files the child process is permited to upload to the web.
  FileMap file_permissions_;

  // The set of files the child process is permitted to load.
  FileSet request_file_set_;

  int enabled_bindings_;

  bool can_read_raw_cookies_;

  bool can_send_midi_sysex_;

  GURL origin_lock_;

  // The set of isolated filesystems the child process is permitted to access.
  FileSystemMap filesystem_permissions_;

  DISALLOW_COPY_AND_ASSIGN(SecurityState);
};

ChildProcessSecurityPolicyImpl::ChildProcessSecurityPolicyImpl() {
  //// We know about these schemes and believe them to be safe.
  //RegisterWebSafeScheme(url::kHttpScheme);
  //RegisterWebSafeScheme(url::kHttpsScheme);
  //RegisterWebSafeScheme(url::kFtpScheme);
  //RegisterWebSafeScheme(url::kDataScheme);
  //RegisterWebSafeScheme("feed");
  //RegisterWebSafeScheme(url::kBlobScheme);
  //RegisterWebSafeScheme(url::kFileSystemScheme);

  //// We know about the following pseudo schemes and treat them specially.
  //RegisterPseudoScheme(url::kAboutScheme);
  //RegisterPseudoScheme(url::kJavaScriptScheme);
  //RegisterPseudoScheme(kViewSourceScheme);
}

ChildProcessSecurityPolicyImpl::~ChildProcessSecurityPolicyImpl() {
  web_safe_schemes_.clear();
  pseudo_schemes_.clear();
  STLDeleteContainerPairSecondPointers(security_state_.begin(),
                                       security_state_.end());
  security_state_.clear();
}

// static
ChildProcessSecurityPolicy* ChildProcessSecurityPolicy::GetInstance() {
  return ChildProcessSecurityPolicyImpl::GetInstance();
}

ChildProcessSecurityPolicyImpl* ChildProcessSecurityPolicyImpl::GetInstance() {
  return Singleton<ChildProcessSecurityPolicyImpl>::get();
}

void ChildProcessSecurityPolicyImpl::Add(int child_id) {
  base::AutoLock lock(lock_);
  AddChild(child_id);
}

void ChildProcessSecurityPolicyImpl::AddWorker(int child_id,
                                               int main_render_process_id) {
  base::AutoLock lock(lock_);
  AddChild(child_id);
  worker_map_[child_id] = main_render_process_id;
}

void ChildProcessSecurityPolicyImpl::Remove(int child_id) {
  base::AutoLock lock(lock_);
  SecurityStateMap::iterator it = security_state_.find(child_id);
  if (it == security_state_.end())
    return;  // May be called multiple times.

  delete it->second;
  security_state_.erase(it);
  worker_map_.erase(child_id);
}

void ChildProcessSecurityPolicyImpl::GrantReadFile(int child_id,
                                                   const base::FilePath& file) {
  GrantPermissionsForFile(child_id, file, READ_FILE_GRANT);
}

void ChildProcessSecurityPolicyImpl::GrantCreateReadWriteFile(
    int child_id, const base::FilePath& file) {
  GrantPermissionsForFile(child_id, file, CREATE_READ_WRITE_FILE_GRANT);
}

void ChildProcessSecurityPolicyImpl::GrantCopyInto(int child_id,
                                                   const base::FilePath& dir) {
  GrantPermissionsForFile(child_id, dir, COPY_INTO_FILE_GRANT);
}

void ChildProcessSecurityPolicyImpl::GrantDeleteFrom(
    int child_id, const base::FilePath& dir) {
  GrantPermissionsForFile(child_id, dir, DELETE_FILE_GRANT);
}

void ChildProcessSecurityPolicyImpl::GrantPermissionsForFile(
    int child_id, const base::FilePath& file, int permissions) {
  base::AutoLock lock(lock_);

  SecurityStateMap::iterator state = security_state_.find(child_id);
  if (state == security_state_.end())
    return;

  state->second->GrantPermissionsForFile(file, permissions);
}

void ChildProcessSecurityPolicyImpl::GrantReadFileSystem(
    int child_id, const std::string& filesystem_id) {
  GrantPermissionsForFileSystem(child_id, filesystem_id, READ_FILE_GRANT);
}

void ChildProcessSecurityPolicyImpl::GrantWriteFileSystem(
    int child_id, const std::string& filesystem_id) {
  GrantPermissionsForFileSystem(child_id, filesystem_id, WRITE_FILE_GRANT);
}

void ChildProcessSecurityPolicyImpl::GrantCreateFileForFileSystem(
    int child_id, const std::string& filesystem_id) {
  GrantPermissionsForFileSystem(child_id, filesystem_id, CREATE_NEW_FILE_GRANT);
}

void ChildProcessSecurityPolicyImpl::GrantCreateReadWriteFileSystem(
    int child_id, const std::string& filesystem_id) {
  GrantPermissionsForFileSystem(
      child_id, filesystem_id, CREATE_READ_WRITE_FILE_GRANT);
}

void ChildProcessSecurityPolicyImpl::GrantCopyIntoFileSystem(
    int child_id, const std::string& filesystem_id) {
  GrantPermissionsForFileSystem(child_id, filesystem_id, COPY_INTO_FILE_GRANT);
}

void ChildProcessSecurityPolicyImpl::GrantDeleteFromFileSystem(
    int child_id, const std::string& filesystem_id) {
  GrantPermissionsForFileSystem(child_id, filesystem_id, DELETE_FILE_GRANT);
}

bool ChildProcessSecurityPolicyImpl::CanReadFile(int child_id,
                                                 const base::FilePath& file) {
  return HasPermissionsForFile(child_id, file, READ_FILE_GRANT);
}

bool ChildProcessSecurityPolicyImpl::CanCreateReadWriteFile(
    int child_id,
    const base::FilePath& file) {
  return HasPermissionsForFile(child_id, file, CREATE_READ_WRITE_FILE_GRANT);
}

bool ChildProcessSecurityPolicyImpl::CanReadFileSystem(
    int child_id, const std::string& filesystem_id) {
  return HasPermissionsForFileSystem(child_id, filesystem_id, READ_FILE_GRANT);
}

bool ChildProcessSecurityPolicyImpl::CanReadWriteFileSystem(
    int child_id, const std::string& filesystem_id) {
  return HasPermissionsForFileSystem(child_id, filesystem_id,
                                     READ_FILE_GRANT | WRITE_FILE_GRANT);
}

bool ChildProcessSecurityPolicyImpl::CanCopyIntoFileSystem(
    int child_id, const std::string& filesystem_id) {
  return HasPermissionsForFileSystem(child_id, filesystem_id,
                                     COPY_INTO_FILE_GRANT);
}

bool ChildProcessSecurityPolicyImpl::CanDeleteFromFileSystem(
    int child_id, const std::string& filesystem_id) {
  return HasPermissionsForFileSystem(child_id, filesystem_id,
                                     DELETE_FILE_GRANT);
}

bool ChildProcessSecurityPolicyImpl::HasPermissionsForFile(
    int child_id, const base::FilePath& file, int permissions) {
  base::AutoLock lock(lock_);
  bool result = ChildProcessHasPermissionsForFile(child_id, file, permissions);
  if (!result) {
    // If this is a worker thread that has no access to a given file,
    // let's check that its renderer process has access to that file instead.
    WorkerToMainProcessMap::iterator iter = worker_map_.find(child_id);
    if (iter != worker_map_.end() && iter->second != 0) {
      result = ChildProcessHasPermissionsForFile(iter->second,
                                                 file,
                                                 permissions);
    }
  }
  return result;
}

//bool ChildProcessSecurityPolicyImpl::HasPermissionsForFileSystemFile(
//    int child_id,
//    const storage::FileSystemURL& url,
//    int permissions) {
//  if (!url.is_valid())
//    return false;
//
//  if (url.path().ReferencesParent())
//    return false;
//
//  // Any write access is disallowed on the root path.
//  if (storage::VirtualPath::IsRootPath(url.path()) &&
//      (permissions & ~READ_FILE_GRANT)) {
//    return false;
//  }
//
//  if (url.mount_type() == storage::kFileSystemTypeIsolated) {
//    // When Isolated filesystems is overlayed on top of another filesystem,
//    // its per-filesystem permission overrides the underlying filesystem
//    // permissions).
//    return HasPermissionsForFileSystem(
//        child_id, url.mount_filesystem_id(), permissions);
//  }
//
//  FileSystemPermissionPolicyMap::iterator found =
//      file_system_policy_map_.find(url.type());
//  if (found == file_system_policy_map_.end())
//    return false;
//
//  if ((found->second & storage::FILE_PERMISSION_READ_ONLY) &&
//      permissions & ~READ_FILE_GRANT) {
//    return false;
//  }
//
//  if (found->second & storage::FILE_PERMISSION_USE_FILE_PERMISSION)
//    return HasPermissionsForFile(child_id, url.path(), permissions);
//
//  if (found->second & storage::FILE_PERMISSION_SANDBOX)
//    return true;
//
//  return false;
//}
//
//bool ChildProcessSecurityPolicyImpl::CanReadFileSystemFile(
//    int child_id,
//    const storage::FileSystemURL& url) {
//  return HasPermissionsForFileSystemFile(child_id, url, READ_FILE_GRANT);
//}
//
//bool ChildProcessSecurityPolicyImpl::CanWriteFileSystemFile(
//    int child_id,
//    const storage::FileSystemURL& url) {
//  return HasPermissionsForFileSystemFile(child_id, url, WRITE_FILE_GRANT);
//}
//
//bool ChildProcessSecurityPolicyImpl::CanCreateFileSystemFile(
//    int child_id,
//    const storage::FileSystemURL& url) {
//  return HasPermissionsForFileSystemFile(child_id, url, CREATE_NEW_FILE_GRANT);
//}
//
//bool ChildProcessSecurityPolicyImpl::CanCreateReadWriteFileSystemFile(
//    int child_id,
//    const storage::FileSystemURL& url) {
//  return HasPermissionsForFileSystemFile(child_id, url,
//                                         CREATE_READ_WRITE_FILE_GRANT);
//}
//
//bool ChildProcessSecurityPolicyImpl::CanCopyIntoFileSystemFile(
//    int child_id,
//    const storage::FileSystemURL& url) {
//  return HasPermissionsForFileSystemFile(child_id, url, COPY_INTO_FILE_GRANT);
//}
//
//bool ChildProcessSecurityPolicyImpl::CanDeleteFileSystemFile(
//    int child_id,
//    const storage::FileSystemURL& url) {
//  return HasPermissionsForFileSystemFile(child_id, url, DELETE_FILE_GRANT);
//}

void ChildProcessSecurityPolicyImpl::AddChild(int child_id) {
  if (security_state_.count(child_id) != 0) {
    NOTREACHED() << "Add child process at most once.";
    return;
  }

  security_state_[child_id] = new SecurityState();
}

bool ChildProcessSecurityPolicyImpl::ChildProcessHasPermissionsForFile(
    int child_id, const base::FilePath& file, int permissions) {
  SecurityStateMap::iterator state = security_state_.find(child_id);
  if (state == security_state_.end())
    return false;
  return state->second->HasPermissionsForFile(file, permissions);
}

void ChildProcessSecurityPolicyImpl::GrantPermissionsForFileSystem(
    int child_id,
    const std::string& filesystem_id,
    int permission) {
  base::AutoLock lock(lock_);

  SecurityStateMap::iterator state = security_state_.find(child_id);
  if (state == security_state_.end())
    return;
  state->second->GrantPermissionsForFileSystem(filesystem_id, permission);
}

bool ChildProcessSecurityPolicyImpl::HasPermissionsForFileSystem(
    int child_id,
    const std::string& filesystem_id,
    int permission) {
  base::AutoLock lock(lock_);

  SecurityStateMap::iterator state = security_state_.find(child_id);
  if (state == security_state_.end())
    return false;
  return state->second->HasPermissionsForFileSystem(filesystem_id, permission);
}

}  // namespace content
