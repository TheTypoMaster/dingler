// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: supersonic/cursor/proto/cursors.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "image/query/cursor/cursors.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace image {

namespace {

const ::google::protobuf::EnumDescriptor* CursorId_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_supersonic_2fcursor_2fproto_2fcursors_2eproto() {
  protobuf_AddDesc_supersonic_2fcursor_2fproto_2fcursors_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "supersonic/cursor/proto/cursors.proto");
  GOOGLE_CHECK(file != NULL);
  CursorId_descriptor_ = file->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_supersonic_2fcursor_2fproto_2fcursors_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
}

}  // namespace

void protobuf_ShutdownFile_supersonic_2fcursor_2fproto_2fcursors_2eproto() {
}

void protobuf_AddDesc_supersonic_2fcursor_2fproto_2fcursors_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n%supersonic/cursor/proto/cursors.proto\022"
    "\nsupersonic*\346\005\n\010CursorId\022\016\n\nFILE_INPUT\020\003"
    "\022\014\n\010GENERATE\020\004\022\023\n\017REPEATING_BLOCK\020\005\022\031\n\025S"
    "ELECTION_VECTOR_VIEW\020\006\022\010\n\004VIEW\020\007\022\026\n\022AGGR"
    "EGATE_CLUSTERS\020\010\022\030\n\024BARRIER_SPLIT_READER"
    "\020\t\022\037\n\033BEST_EFFORT_GROUP_AGGREGATE\020\n\022\031\n\025B"
    "UFFERED_SPLIT_READER\020\013\022\026\n\022CANCELLATION_W"
    "ATCH\020\014\022\014\n\010COALESCE\020\r\022\013\n\007COMPUTE\020\017\022\n\n\006FIL"
    "TER\020\020\022\022\n\016FOREIGN_FILTER\020\021\022\023\n\017GROUP_AGGRE"
    "GATE\020\022\022\r\n\tHASH_JOIN\020\023\022\"\n\036HYBRID_GROUP_FI"
    "NAL_AGGREGATION\020\024\022\032\n\026HYBRID_GROUP_TRANSF"
    "ORM\020\025\022\t\n\005LIMIT\020\026\022\017\n\013LOOKUP_JOIN\020\027\022\023\n\017MER"
    "GE_UNION_ALL\020\030\022\022\n\016PARALLEL_UNION\020\031\022\013\n\007PR"
    "OJECT\020\032\022\024\n\020ROWID_MERGE_JOIN\020\034\022\024\n\020SCALAR_"
    "AGGREGATE\020\035\022\010\n\004SORT\020\036\022\r\n\tDECORATOR\020 \022\023\n\017"
    "OWNERSHIP_TAKER\020!\022\023\n\017READ_STATISTICS\020\"\022\024"
    "\n\020BARRIER_INJECTOR\020#\022\025\n\021BARRIER_SWALLOWE"
    "R\020$\022\r\n\tBENCHMARK\020%\022\020\n\014DEEP_COPYING\020&\022\030\n\024"
    "INTERRUPTION_COUNTER\020\'\022\022\n\016TEST_DECORATOR"
    "\020(\022\020\n\014VIEW_LIMITER\020)\022\016\n\nUNKNOWN_ID\020*", 796);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "supersonic/cursor/proto/cursors.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_supersonic_2fcursor_2fproto_2fcursors_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_supersonic_2fcursor_2fproto_2fcursors_2eproto {
  StaticDescriptorInitializer_supersonic_2fcursor_2fproto_2fcursors_2eproto() {
    protobuf_AddDesc_supersonic_2fcursor_2fproto_2fcursors_2eproto();
  }
} static_descriptor_initializer_supersonic_2fcursor_2fproto_2fcursors_2eproto_;
const ::google::protobuf::EnumDescriptor* CursorId_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return CursorId_descriptor_;
}
bool CursorId_IsValid(int value) {
  switch(value) {
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 28:
    case 29:
    case 30:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
    case 41:
    case 42:
      return true;
    default:
      return false;
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace image

// @@protoc_insertion_point(global_scope)
