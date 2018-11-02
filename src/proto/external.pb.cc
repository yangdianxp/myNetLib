// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: external.proto

#include "external.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// This is a temporary google only hack
#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
#include "third_party/protobuf/version.h"
#endif
// @@protoc_insertion_point(includes)

namespace pb {
namespace external {
class modify_channelDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<modify_channel>
      _instance;
} _modify_channel_default_instance_;
}  // namespace external
}  // namespace pb
namespace protobuf_external_2eproto {
static void InitDefaultsmodify_channel() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::pb::external::_modify_channel_default_instance_;
    new (ptr) ::pb::external::modify_channel();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::pb::external::modify_channel::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_modify_channel =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsmodify_channel}, {}};

void InitDefaults() {
  ::google::protobuf::internal::InitSCC(&scc_info_modify_channel.base);
}

::google::protobuf::Metadata file_level_metadata[1];

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pb::external::modify_channel, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pb::external::modify_channel, type_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pb::external::modify_channel, tid_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pb::external::modify_channel, uid_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pb::external::modify_channel, vid_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pb::external::modify_channel, src_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pb::external::modify_channel, dst_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::pb::external::modify_channel)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::pb::external::_modify_channel_default_instance_),
};

void protobuf_AssignDescriptors() {
  AddDescriptors();
  AssignDescriptors(
      "external.proto", schemas, file_default_instances, TableStruct::offsets,
      file_level_metadata, NULL, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static ::google::protobuf::internal::once_flag once;
  ::google::protobuf::internal::call_once(once, protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_PROTOBUF_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 1);
}

void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\016external.proto\022\013pb.external\"_\n\016modify_"
      "channel\022\014\n\004type\030\001 \001(\005\022\013\n\003tid\030\002 \001(\005\022\013\n\003ui"
      "d\030\003 \001(\005\022\013\n\003vid\030\004 \001(\005\022\013\n\003src\030\005 \001(\005\022\013\n\003dst"
      "\030\006 \001(\005b\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 134);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "external.proto", &protobuf_RegisterTypes);
}

void AddDescriptors() {
  static ::google::protobuf::internal::once_flag once;
  ::google::protobuf::internal::call_once(once, AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;
}  // namespace protobuf_external_2eproto
namespace pb {
namespace external {

// ===================================================================

void modify_channel::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int modify_channel::kTypeFieldNumber;
const int modify_channel::kTidFieldNumber;
const int modify_channel::kUidFieldNumber;
const int modify_channel::kVidFieldNumber;
const int modify_channel::kSrcFieldNumber;
const int modify_channel::kDstFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

modify_channel::modify_channel()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  ::google::protobuf::internal::InitSCC(
      &protobuf_external_2eproto::scc_info_modify_channel.base);
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.external.modify_channel)
}
modify_channel::modify_channel(const modify_channel& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&type_, &from.type_,
    static_cast<size_t>(reinterpret_cast<char*>(&dst_) -
    reinterpret_cast<char*>(&type_)) + sizeof(dst_));
  // @@protoc_insertion_point(copy_constructor:pb.external.modify_channel)
}

void modify_channel::SharedCtor() {
  ::memset(&type_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&dst_) -
      reinterpret_cast<char*>(&type_)) + sizeof(dst_));
}

modify_channel::~modify_channel() {
  // @@protoc_insertion_point(destructor:pb.external.modify_channel)
  SharedDtor();
}

void modify_channel::SharedDtor() {
}

void modify_channel::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ::google::protobuf::Descriptor* modify_channel::descriptor() {
  ::protobuf_external_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_external_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const modify_channel& modify_channel::default_instance() {
  ::google::protobuf::internal::InitSCC(&protobuf_external_2eproto::scc_info_modify_channel.base);
  return *internal_default_instance();
}


void modify_channel::Clear() {
// @@protoc_insertion_point(message_clear_start:pb.external.modify_channel)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&type_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&dst_) -
      reinterpret_cast<char*>(&type_)) + sizeof(dst_));
  _internal_metadata_.Clear();
}

bool modify_channel::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.external.modify_channel)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // int32 type = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &type_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // int32 tid = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(16u /* 16 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &tid_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // int32 uid = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(24u /* 24 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &uid_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // int32 vid = 4;
      case 4: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(32u /* 32 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &vid_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // int32 src = 5;
      case 5: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(40u /* 40 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &src_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // int32 dst = 6;
      case 6: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(48u /* 48 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &dst_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:pb.external.modify_channel)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.external.modify_channel)
  return false;
#undef DO_
}

void modify_channel::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.external.modify_channel)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 type = 1;
  if (this->type() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->type(), output);
  }

  // int32 tid = 2;
  if (this->tid() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->tid(), output);
  }

  // int32 uid = 3;
  if (this->uid() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->uid(), output);
  }

  // int32 vid = 4;
  if (this->vid() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(4, this->vid(), output);
  }

  // int32 src = 5;
  if (this->src() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(5, this->src(), output);
  }

  // int32 dst = 6;
  if (this->dst() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(6, this->dst(), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.external.modify_channel)
}

::google::protobuf::uint8* modify_channel::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:pb.external.modify_channel)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 type = 1;
  if (this->type() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->type(), target);
  }

  // int32 tid = 2;
  if (this->tid() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->tid(), target);
  }

  // int32 uid = 3;
  if (this->uid() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->uid(), target);
  }

  // int32 vid = 4;
  if (this->vid() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(4, this->vid(), target);
  }

  // int32 src = 5;
  if (this->src() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(5, this->src(), target);
  }

  // int32 dst = 6;
  if (this->dst() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(6, this->dst(), target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.external.modify_channel)
  return target;
}

size_t modify_channel::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:pb.external.modify_channel)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // int32 type = 1;
  if (this->type() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->type());
  }

  // int32 tid = 2;
  if (this->tid() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->tid());
  }

  // int32 uid = 3;
  if (this->uid() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->uid());
  }

  // int32 vid = 4;
  if (this->vid() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->vid());
  }

  // int32 src = 5;
  if (this->src() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->src());
  }

  // int32 dst = 6;
  if (this->dst() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->dst());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void modify_channel::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:pb.external.modify_channel)
  GOOGLE_DCHECK_NE(&from, this);
  const modify_channel* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const modify_channel>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:pb.external.modify_channel)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:pb.external.modify_channel)
    MergeFrom(*source);
  }
}

void modify_channel::MergeFrom(const modify_channel& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:pb.external.modify_channel)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.type() != 0) {
    set_type(from.type());
  }
  if (from.tid() != 0) {
    set_tid(from.tid());
  }
  if (from.uid() != 0) {
    set_uid(from.uid());
  }
  if (from.vid() != 0) {
    set_vid(from.vid());
  }
  if (from.src() != 0) {
    set_src(from.src());
  }
  if (from.dst() != 0) {
    set_dst(from.dst());
  }
}

void modify_channel::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:pb.external.modify_channel)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void modify_channel::CopyFrom(const modify_channel& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:pb.external.modify_channel)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool modify_channel::IsInitialized() const {
  return true;
}

void modify_channel::Swap(modify_channel* other) {
  if (other == this) return;
  InternalSwap(other);
}
void modify_channel::InternalSwap(modify_channel* other) {
  using std::swap;
  swap(type_, other->type_);
  swap(tid_, other->tid_);
  swap(uid_, other->uid_);
  swap(vid_, other->vid_);
  swap(src_, other->src_);
  swap(dst_, other->dst_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata modify_channel::GetMetadata() const {
  protobuf_external_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_external_2eproto::file_level_metadata[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace external
}  // namespace pb
namespace google {
namespace protobuf {
template<> GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::pb::external::modify_channel* Arena::CreateMaybeMessage< ::pb::external::modify_channel >(Arena* arena) {
  return Arena::CreateInternal< ::pb::external::modify_channel >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
