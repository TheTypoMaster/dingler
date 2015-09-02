// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: supersonic/utils/exception/stack_trace.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "image/query/utils/stack_trace.pb.h"

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

const ::google::protobuf::Descriptor* StackTrace_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  StackTrace_reflection_ = NULL;
const ::google::protobuf::Descriptor* StackTrace_Element_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  StackTrace_Element_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_supersonic_2futils_2fexception_2fstack_5ftrace_2eproto() {
  protobuf_AddDesc_supersonic_2futils_2fexception_2fstack_5ftrace_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "supersonic/utils/exception/stack_trace.proto");
  GOOGLE_CHECK(file != NULL);
  StackTrace_descriptor_ = file->message_type(0);
  static const int StackTrace_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StackTrace, element_),
  };
  StackTrace_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      StackTrace_descriptor_,
      StackTrace::default_instance_,
      StackTrace_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StackTrace, _has_bits_[0]),
      -1,
      -1,
      sizeof(StackTrace),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StackTrace, _internal_metadata_),
      -1);
  StackTrace_Element_descriptor_ = StackTrace_descriptor_->nested_type(0);
  static const int StackTrace_Element_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StackTrace_Element, function_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StackTrace_Element, filename_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StackTrace_Element, line_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StackTrace_Element, context_),
  };
  StackTrace_Element_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      StackTrace_Element_descriptor_,
      StackTrace_Element::default_instance_,
      StackTrace_Element_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StackTrace_Element, _has_bits_[0]),
      -1,
      -1,
      sizeof(StackTrace_Element),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StackTrace_Element, _internal_metadata_),
      -1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_supersonic_2futils_2fexception_2fstack_5ftrace_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      StackTrace_descriptor_, &StackTrace::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      StackTrace_Element_descriptor_, &StackTrace_Element::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_supersonic_2futils_2fexception_2fstack_5ftrace_2eproto() {
  delete StackTrace::default_instance_;
  delete StackTrace_reflection_;
  delete StackTrace_Element::default_instance_;
  delete StackTrace_Element_reflection_;
}

void protobuf_AddDesc_supersonic_2futils_2fexception_2fstack_5ftrace_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n,supersonic/utils/exception/stack_trace"
    ".proto\022\006common\"\213\001\n\nStackTrace\022+\n\007element"
    "\030\001 \003(\0132\032.common.StackTrace.Element\032P\n\007El"
    "ement\022\020\n\010function\030\001 \001(\t\022\020\n\010filename\030\002 \001("
    "\t\022\020\n\004line\030\003 \001(\005:\002-1\022\017\n\007context\030\004 \001(\tB6\n)"
    "com.google.datawarehouse.common.exceptio"
    "nB\tException", 252);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "supersonic/utils/exception/stack_trace.proto", &protobuf_RegisterTypes);
  StackTrace::default_instance_ = new StackTrace();
  StackTrace_Element::default_instance_ = new StackTrace_Element();
  StackTrace::default_instance_->InitAsDefaultInstance();
  StackTrace_Element::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_supersonic_2futils_2fexception_2fstack_5ftrace_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_supersonic_2futils_2fexception_2fstack_5ftrace_2eproto {
  StaticDescriptorInitializer_supersonic_2futils_2fexception_2fstack_5ftrace_2eproto() {
    protobuf_AddDesc_supersonic_2futils_2fexception_2fstack_5ftrace_2eproto();
  }
} static_descriptor_initializer_supersonic_2futils_2fexception_2fstack_5ftrace_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
static void MergeFromFail(int line) {
  GOOGLE_CHECK(false) << __FILE__ << ":" << line;
}

}  // namespace


// ===================================================================

#ifndef _MSC_VER
const int StackTrace_Element::kFunctionFieldNumber;
const int StackTrace_Element::kFilenameFieldNumber;
const int StackTrace_Element::kLineFieldNumber;
const int StackTrace_Element::kContextFieldNumber;
#endif  // !_MSC_VER

StackTrace_Element::StackTrace_Element()
  : ::google::protobuf::Message() , _internal_metadata_(NULL)  {
  SharedCtor();
  // @@protoc_insertion_point(constructor:common.StackTrace.Element)
}

void StackTrace_Element::InitAsDefaultInstance() {
}

StackTrace_Element::StackTrace_Element(const StackTrace_Element& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:common.StackTrace.Element)
}

void StackTrace_Element::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  function_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  filename_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  line_ = -1;
  context_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

StackTrace_Element::~StackTrace_Element() {
  // @@protoc_insertion_point(destructor:common.StackTrace.Element)
  SharedDtor();
}

void StackTrace_Element::SharedDtor() {
  function_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  filename_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  context_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (this != default_instance_) {
  }
}

void StackTrace_Element::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* StackTrace_Element::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return StackTrace_Element_descriptor_;
}

const StackTrace_Element& StackTrace_Element::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_supersonic_2futils_2fexception_2fstack_5ftrace_2eproto();
  return *default_instance_;
}

StackTrace_Element* StackTrace_Element::default_instance_ = NULL;

StackTrace_Element* StackTrace_Element::New(::google::protobuf::Arena* arena) const {
  StackTrace_Element* n = new StackTrace_Element;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void StackTrace_Element::Clear() {
  if (_has_bits_[0 / 32] & 15u) {
    if (has_function()) {
      function_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    }
    if (has_filename()) {
      filename_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    }
    line_ = -1;
    if (has_context()) {
      context_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool StackTrace_Element::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:common.StackTrace.Element)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string function = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_function()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->function().data(), this->function().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "common.StackTrace.Element.function");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_filename;
        break;
      }

      // optional string filename = 2;
      case 2: {
        if (tag == 18) {
         parse_filename:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_filename()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->filename().data(), this->filename().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "common.StackTrace.Element.filename");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_line;
        break;
      }

      // optional int32 line = 3 [default = -1];
      case 3: {
        if (tag == 24) {
         parse_line:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &line_)));
          set_has_line();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(34)) goto parse_context;
        break;
      }

      // optional string context = 4;
      case 4: {
        if (tag == 34) {
         parse_context:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_context()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->context().data(), this->context().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "common.StackTrace.Element.context");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:common.StackTrace.Element)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:common.StackTrace.Element)
  return false;
#undef DO_
}

void StackTrace_Element::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:common.StackTrace.Element)
  // optional string function = 1;
  if (has_function()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->function().data(), this->function().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "common.StackTrace.Element.function");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->function(), output);
  }

  // optional string filename = 2;
  if (has_filename()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->filename().data(), this->filename().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "common.StackTrace.Element.filename");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->filename(), output);
  }

  // optional int32 line = 3 [default = -1];
  if (has_line()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->line(), output);
  }

  // optional string context = 4;
  if (has_context()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->context().data(), this->context().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "common.StackTrace.Element.context");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      4, this->context(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:common.StackTrace.Element)
}

::google::protobuf::uint8* StackTrace_Element::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:common.StackTrace.Element)
  // optional string function = 1;
  if (has_function()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->function().data(), this->function().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "common.StackTrace.Element.function");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->function(), target);
  }

  // optional string filename = 2;
  if (has_filename()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->filename().data(), this->filename().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "common.StackTrace.Element.filename");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->filename(), target);
  }

  // optional int32 line = 3 [default = -1];
  if (has_line()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->line(), target);
  }

  // optional string context = 4;
  if (has_context()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->context().data(), this->context().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "common.StackTrace.Element.context");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        4, this->context(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:common.StackTrace.Element)
  return target;
}

int StackTrace_Element::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & 15) {
    // optional string function = 1;
    if (has_function()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->function());
    }

    // optional string filename = 2;
    if (has_filename()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->filename());
    }

    // optional int32 line = 3 [default = -1];
    if (has_line()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->line());
    }

    // optional string context = 4;
    if (has_context()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->context());
    }

  }
  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void StackTrace_Element::MergeFrom(const ::google::protobuf::Message& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const StackTrace_Element* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const StackTrace_Element*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void StackTrace_Element::MergeFrom(const StackTrace_Element& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_function()) {
      set_has_function();
      function_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.function_);
    }
    if (from.has_filename()) {
      set_has_filename();
      filename_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.filename_);
    }
    if (from.has_line()) {
      set_line(from.line());
    }
    if (from.has_context()) {
      set_has_context();
      context_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.context_);
    }
  }
  if (from._internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
  }
}

void StackTrace_Element::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void StackTrace_Element::CopyFrom(const StackTrace_Element& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool StackTrace_Element::IsInitialized() const {

  return true;
}

void StackTrace_Element::Swap(StackTrace_Element* other) {
  if (other == this) return;
  InternalSwap(other);
}
void StackTrace_Element::InternalSwap(StackTrace_Element* other) {
  function_.Swap(&other->function_);
  filename_.Swap(&other->filename_);
  std::swap(line_, other->line_);
  context_.Swap(&other->context_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata StackTrace_Element::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = StackTrace_Element_descriptor_;
  metadata.reflection = StackTrace_Element_reflection_;
  return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int StackTrace::kElementFieldNumber;
#endif  // !_MSC_VER

StackTrace::StackTrace()
  : ::google::protobuf::Message() , _internal_metadata_(NULL)  {
  SharedCtor();
  // @@protoc_insertion_point(constructor:common.StackTrace)
}

void StackTrace::InitAsDefaultInstance() {
}

StackTrace::StackTrace(const StackTrace& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:common.StackTrace)
}

void StackTrace::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

StackTrace::~StackTrace() {
  // @@protoc_insertion_point(destructor:common.StackTrace)
  SharedDtor();
}

void StackTrace::SharedDtor() {
  if (this != default_instance_) {
  }
}

void StackTrace::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* StackTrace::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return StackTrace_descriptor_;
}

const StackTrace& StackTrace::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_supersonic_2futils_2fexception_2fstack_5ftrace_2eproto();
  return *default_instance_;
}

StackTrace* StackTrace::default_instance_ = NULL;

StackTrace* StackTrace::New(::google::protobuf::Arena* arena) const {
  StackTrace* n = new StackTrace;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void StackTrace::Clear() {
  element_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool StackTrace::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:common.StackTrace)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .common.StackTrace.Element element = 1;
      case 1: {
        if (tag == 10) {
         parse_element:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_element()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(10)) goto parse_element;
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:common.StackTrace)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:common.StackTrace)
  return false;
#undef DO_
}

void StackTrace::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:common.StackTrace)
  // repeated .common.StackTrace.Element element = 1;
  for (unsigned int i = 0, n = this->element_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->element(i), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:common.StackTrace)
}

::google::protobuf::uint8* StackTrace::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:common.StackTrace)
  // repeated .common.StackTrace.Element element = 1;
  for (unsigned int i = 0, n = this->element_size(); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->element(i), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:common.StackTrace)
  return target;
}

int StackTrace::ByteSize() const {
  int total_size = 0;

  // repeated .common.StackTrace.Element element = 1;
  total_size += 1 * this->element_size();
  for (int i = 0; i < this->element_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->element(i));
  }

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void StackTrace::MergeFrom(const ::google::protobuf::Message& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const StackTrace* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const StackTrace*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void StackTrace::MergeFrom(const StackTrace& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  element_.MergeFrom(from.element_);
  if (from._internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
  }
}

void StackTrace::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void StackTrace::CopyFrom(const StackTrace& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool StackTrace::IsInitialized() const {

  return true;
}

void StackTrace::Swap(StackTrace* other) {
  if (other == this) return;
  InternalSwap(other);
}
void StackTrace::InternalSwap(StackTrace* other) {
  element_.UnsafeArenaSwap(&other->element_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata StackTrace::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = StackTrace_descriptor_;
  metadata.reflection = StackTrace_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// StackTrace_Element

// optional string function = 1;
 bool StackTrace_Element::has_function() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
 void StackTrace_Element::set_has_function() {
  _has_bits_[0] |= 0x00000001u;
}
 void StackTrace_Element::clear_has_function() {
  _has_bits_[0] &= ~0x00000001u;
}
 void StackTrace_Element::clear_function() {
  function_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_function();
}
 const ::std::string& StackTrace_Element::function() const {
  // @@protoc_insertion_point(field_get:common.StackTrace.Element.function)
  return function_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void StackTrace_Element::set_function(const ::std::string& value) {
  set_has_function();
  function_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:common.StackTrace.Element.function)
}
 void StackTrace_Element::set_function(const char* value) {
  set_has_function();
  function_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:common.StackTrace.Element.function)
}
 void StackTrace_Element::set_function(const char* value, size_t size) {
  set_has_function();
  function_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:common.StackTrace.Element.function)
}
 ::std::string* StackTrace_Element::mutable_function() {
  set_has_function();
  // @@protoc_insertion_point(field_mutable:common.StackTrace.Element.function)
  return function_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* StackTrace_Element::release_function() {
  clear_has_function();
  return function_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void StackTrace_Element::set_allocated_function(::std::string* function) {
  if (function != NULL) {
    set_has_function();
  } else {
    clear_has_function();
  }
  function_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), function);
  // @@protoc_insertion_point(field_set_allocated:common.StackTrace.Element.function)
}

// optional string filename = 2;
 bool StackTrace_Element::has_filename() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
 void StackTrace_Element::set_has_filename() {
  _has_bits_[0] |= 0x00000002u;
}
 void StackTrace_Element::clear_has_filename() {
  _has_bits_[0] &= ~0x00000002u;
}
 void StackTrace_Element::clear_filename() {
  filename_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_filename();
}
 const ::std::string& StackTrace_Element::filename() const {
  // @@protoc_insertion_point(field_get:common.StackTrace.Element.filename)
  return filename_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void StackTrace_Element::set_filename(const ::std::string& value) {
  set_has_filename();
  filename_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:common.StackTrace.Element.filename)
}
 void StackTrace_Element::set_filename(const char* value) {
  set_has_filename();
  filename_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:common.StackTrace.Element.filename)
}
 void StackTrace_Element::set_filename(const char* value, size_t size) {
  set_has_filename();
  filename_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:common.StackTrace.Element.filename)
}
 ::std::string* StackTrace_Element::mutable_filename() {
  set_has_filename();
  // @@protoc_insertion_point(field_mutable:common.StackTrace.Element.filename)
  return filename_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* StackTrace_Element::release_filename() {
  clear_has_filename();
  return filename_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void StackTrace_Element::set_allocated_filename(::std::string* filename) {
  if (filename != NULL) {
    set_has_filename();
  } else {
    clear_has_filename();
  }
  filename_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), filename);
  // @@protoc_insertion_point(field_set_allocated:common.StackTrace.Element.filename)
}

// optional int32 line = 3 [default = -1];
 bool StackTrace_Element::has_line() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
 void StackTrace_Element::set_has_line() {
  _has_bits_[0] |= 0x00000004u;
}
 void StackTrace_Element::clear_has_line() {
  _has_bits_[0] &= ~0x00000004u;
}
 void StackTrace_Element::clear_line() {
  line_ = -1;
  clear_has_line();
}
 ::google::protobuf::int32 StackTrace_Element::line() const {
  // @@protoc_insertion_point(field_get:common.StackTrace.Element.line)
  return line_;
}
 void StackTrace_Element::set_line(::google::protobuf::int32 value) {
  set_has_line();
  line_ = value;
  // @@protoc_insertion_point(field_set:common.StackTrace.Element.line)
}

// optional string context = 4;
 bool StackTrace_Element::has_context() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
 void StackTrace_Element::set_has_context() {
  _has_bits_[0] |= 0x00000008u;
}
 void StackTrace_Element::clear_has_context() {
  _has_bits_[0] &= ~0x00000008u;
}
 void StackTrace_Element::clear_context() {
  context_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_context();
}
 const ::std::string& StackTrace_Element::context() const {
  // @@protoc_insertion_point(field_get:common.StackTrace.Element.context)
  return context_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void StackTrace_Element::set_context(const ::std::string& value) {
  set_has_context();
  context_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:common.StackTrace.Element.context)
}
 void StackTrace_Element::set_context(const char* value) {
  set_has_context();
  context_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:common.StackTrace.Element.context)
}
 void StackTrace_Element::set_context(const char* value, size_t size) {
  set_has_context();
  context_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:common.StackTrace.Element.context)
}
 ::std::string* StackTrace_Element::mutable_context() {
  set_has_context();
  // @@protoc_insertion_point(field_mutable:common.StackTrace.Element.context)
  return context_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* StackTrace_Element::release_context() {
  clear_has_context();
  return context_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void StackTrace_Element::set_allocated_context(::std::string* context) {
  if (context != NULL) {
    set_has_context();
  } else {
    clear_has_context();
  }
  context_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), context);
  // @@protoc_insertion_point(field_set_allocated:common.StackTrace.Element.context)
}

// -------------------------------------------------------------------

// StackTrace

// repeated .common.StackTrace.Element element = 1;
 int StackTrace::element_size() const {
  return element_.size();
}
 void StackTrace::clear_element() {
  element_.Clear();
}
 const ::container::StackTrace_Element& StackTrace::element(int index) const {
  // @@protoc_insertion_point(field_get:common.StackTrace.element)
  return element_.Get(index);
}
 ::container::StackTrace_Element* StackTrace::mutable_element(int index) {
  // @@protoc_insertion_point(field_mutable:common.StackTrace.element)
  return element_.Mutable(index);
}
 ::container::StackTrace_Element* StackTrace::add_element() {
  // @@protoc_insertion_point(field_add:common.StackTrace.element)
  return element_.Add();
}
 const ::google::protobuf::RepeatedPtrField< ::container::StackTrace_Element >&
StackTrace::element() const {
  // @@protoc_insertion_point(field_list:common.StackTrace.element)
  return element_;
}
 ::google::protobuf::RepeatedPtrField< ::container::StackTrace_Element >*
StackTrace::mutable_element() {
  // @@protoc_insertion_point(field_mutable_list:common.StackTrace.element)
  return &element_;
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace common

// @@protoc_insertion_point(global_scope)