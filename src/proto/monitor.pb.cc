// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: monitor.proto

#include "monitor.pb.h"

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

namespace protobuf_internal_2eproto {
extern PROTOBUF_INTERNAL_EXPORT_protobuf_internal_2eproto ::google::protobuf::internal::SCCInfo<0> scc_info_register_info;
}  // namespace protobuf_internal_2eproto
namespace pb {
namespace monitor {
class cmdDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<cmd>
      _instance;
} _cmd_default_instance_;
class module_listDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<module_list>
      _instance;
} _module_list_default_instance_;
}  // namespace monitor
}  // namespace pb
namespace protobuf_monitor_2eproto {
static void InitDefaultscmd() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::pb::monitor::_cmd_default_instance_;
    new (ptr) ::pb::monitor::cmd();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::pb::monitor::cmd::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_cmd =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultscmd}, {}};

static void InitDefaultsmodule_list() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::pb::monitor::_module_list_default_instance_;
    new (ptr) ::pb::monitor::module_list();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::pb::monitor::module_list::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<1> scc_info_module_list =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 1, InitDefaultsmodule_list}, {
      &protobuf_internal_2eproto::scc_info_register_info.base,}};

void InitDefaults() {
  ::google::protobuf::internal::InitSCC(&scc_info_cmd.base);
  ::google::protobuf::internal::InitSCC(&scc_info_module_list.base);
}

::google::protobuf::Metadata file_level_metadata[2];

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pb::monitor::cmd, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pb::monitor::cmd, content_),
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pb::monitor::module_list, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pb::monitor::module_list, clients_size_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pb::monitor::module_list, type_clients_size_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pb::monitor::module_list, mid_clients_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::pb::monitor::cmd)},
  { 6, -1, sizeof(::pb::monitor::module_list)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::pb::monitor::_cmd_default_instance_),
  reinterpret_cast<const ::google::protobuf::Message*>(&::pb::monitor::_module_list_default_instance_),
};

void protobuf_AssignDescriptors() {
  AddDescriptors();
  AssignDescriptors(
      "monitor.proto", schemas, file_default_instances, TableStruct::offsets,
      file_level_metadata, NULL, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static ::google::protobuf::internal::once_flag once;
  ::google::protobuf::internal::call_once(once, protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_PROTOBUF_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 2);
}

void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\rmonitor.proto\022\npb.monitor\032\016internal.pr"
      "oto\"\026\n\003cmd\022\017\n\007content\030\001 \001(\t\"o\n\013module_li"
      "st\022\024\n\014clients_size\030\001 \001(\005\022\031\n\021type_clients"
      "_size\030\002 \001(\005\022/\n\013mid_clients\030\003 \003(\0132\032.pb.in"
      "ternal.register_infob\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 188);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "monitor.proto", &protobuf_RegisterTypes);
  ::protobuf_internal_2eproto::AddDescriptors();
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
}  // namespace protobuf_monitor_2eproto
namespace pb {
namespace monitor {

// ===================================================================

void cmd::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int cmd::kContentFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

cmd::cmd()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  ::google::protobuf::internal::InitSCC(
      &protobuf_monitor_2eproto::scc_info_cmd.base);
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.monitor.cmd)
}
cmd::cmd(const cmd& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  content_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.content().size() > 0) {
    content_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.content_);
  }
  // @@protoc_insertion_point(copy_constructor:pb.monitor.cmd)
}

void cmd::SharedCtor() {
  content_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

cmd::~cmd() {
  // @@protoc_insertion_point(destructor:pb.monitor.cmd)
  SharedDtor();
}

void cmd::SharedDtor() {
  content_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void cmd::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ::google::protobuf::Descriptor* cmd::descriptor() {
  ::protobuf_monitor_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_monitor_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const cmd& cmd::default_instance() {
  ::google::protobuf::internal::InitSCC(&protobuf_monitor_2eproto::scc_info_cmd.base);
  return *internal_default_instance();
}


void cmd::Clear() {
// @@protoc_insertion_point(message_clear_start:pb.monitor.cmd)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  content_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  _internal_metadata_.Clear();
}

bool cmd::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.monitor.cmd)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // string content = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_content()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->content().data(), static_cast<int>(this->content().length()),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "pb.monitor.cmd.content"));
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
  // @@protoc_insertion_point(parse_success:pb.monitor.cmd)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.monitor.cmd)
  return false;
#undef DO_
}

void cmd::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.monitor.cmd)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string content = 1;
  if (this->content().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->content().data(), static_cast<int>(this->content().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "pb.monitor.cmd.content");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->content(), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.monitor.cmd)
}

::google::protobuf::uint8* cmd::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:pb.monitor.cmd)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string content = 1;
  if (this->content().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->content().data(), static_cast<int>(this->content().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "pb.monitor.cmd.content");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->content(), target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.monitor.cmd)
  return target;
}

size_t cmd::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:pb.monitor.cmd)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // string content = 1;
  if (this->content().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->content());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void cmd::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:pb.monitor.cmd)
  GOOGLE_DCHECK_NE(&from, this);
  const cmd* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const cmd>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:pb.monitor.cmd)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:pb.monitor.cmd)
    MergeFrom(*source);
  }
}

void cmd::MergeFrom(const cmd& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:pb.monitor.cmd)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.content().size() > 0) {

    content_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.content_);
  }
}

void cmd::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:pb.monitor.cmd)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void cmd::CopyFrom(const cmd& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:pb.monitor.cmd)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool cmd::IsInitialized() const {
  return true;
}

void cmd::Swap(cmd* other) {
  if (other == this) return;
  InternalSwap(other);
}
void cmd::InternalSwap(cmd* other) {
  using std::swap;
  content_.Swap(&other->content_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata cmd::GetMetadata() const {
  protobuf_monitor_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_monitor_2eproto::file_level_metadata[kIndexInFileMessages];
}


// ===================================================================

void module_list::InitAsDefaultInstance() {
}
void module_list::clear_mid_clients() {
  mid_clients_.Clear();
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int module_list::kClientsSizeFieldNumber;
const int module_list::kTypeClientsSizeFieldNumber;
const int module_list::kMidClientsFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

module_list::module_list()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  ::google::protobuf::internal::InitSCC(
      &protobuf_monitor_2eproto::scc_info_module_list.base);
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.monitor.module_list)
}
module_list::module_list(const module_list& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      mid_clients_(from.mid_clients_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&clients_size_, &from.clients_size_,
    static_cast<size_t>(reinterpret_cast<char*>(&type_clients_size_) -
    reinterpret_cast<char*>(&clients_size_)) + sizeof(type_clients_size_));
  // @@protoc_insertion_point(copy_constructor:pb.monitor.module_list)
}

void module_list::SharedCtor() {
  ::memset(&clients_size_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&type_clients_size_) -
      reinterpret_cast<char*>(&clients_size_)) + sizeof(type_clients_size_));
}

module_list::~module_list() {
  // @@protoc_insertion_point(destructor:pb.monitor.module_list)
  SharedDtor();
}

void module_list::SharedDtor() {
}

void module_list::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ::google::protobuf::Descriptor* module_list::descriptor() {
  ::protobuf_monitor_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_monitor_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const module_list& module_list::default_instance() {
  ::google::protobuf::internal::InitSCC(&protobuf_monitor_2eproto::scc_info_module_list.base);
  return *internal_default_instance();
}


void module_list::Clear() {
// @@protoc_insertion_point(message_clear_start:pb.monitor.module_list)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  mid_clients_.Clear();
  ::memset(&clients_size_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&type_clients_size_) -
      reinterpret_cast<char*>(&clients_size_)) + sizeof(type_clients_size_));
  _internal_metadata_.Clear();
}

bool module_list::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.monitor.module_list)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // int32 clients_size = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &clients_size_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // int32 type_clients_size = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(16u /* 16 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &type_clients_size_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // repeated .pb.internal.register_info mid_clients = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(26u /* 26 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessage(
                input, add_mid_clients()));
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
  // @@protoc_insertion_point(parse_success:pb.monitor.module_list)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.monitor.module_list)
  return false;
#undef DO_
}

void module_list::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.monitor.module_list)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 clients_size = 1;
  if (this->clients_size() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->clients_size(), output);
  }

  // int32 type_clients_size = 2;
  if (this->type_clients_size() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->type_clients_size(), output);
  }

  // repeated .pb.internal.register_info mid_clients = 3;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->mid_clients_size()); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3,
      this->mid_clients(static_cast<int>(i)),
      output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.monitor.module_list)
}

::google::protobuf::uint8* module_list::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:pb.monitor.module_list)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 clients_size = 1;
  if (this->clients_size() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->clients_size(), target);
  }

  // int32 type_clients_size = 2;
  if (this->type_clients_size() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->type_clients_size(), target);
  }

  // repeated .pb.internal.register_info mid_clients = 3;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->mid_clients_size()); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageToArray(
        3, this->mid_clients(static_cast<int>(i)), deterministic, target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.monitor.module_list)
  return target;
}

size_t module_list::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:pb.monitor.module_list)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // repeated .pb.internal.register_info mid_clients = 3;
  {
    unsigned int count = static_cast<unsigned int>(this->mid_clients_size());
    total_size += 1UL * count;
    for (unsigned int i = 0; i < count; i++) {
      total_size +=
        ::google::protobuf::internal::WireFormatLite::MessageSize(
          this->mid_clients(static_cast<int>(i)));
    }
  }

  // int32 clients_size = 1;
  if (this->clients_size() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->clients_size());
  }

  // int32 type_clients_size = 2;
  if (this->type_clients_size() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->type_clients_size());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void module_list::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:pb.monitor.module_list)
  GOOGLE_DCHECK_NE(&from, this);
  const module_list* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const module_list>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:pb.monitor.module_list)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:pb.monitor.module_list)
    MergeFrom(*source);
  }
}

void module_list::MergeFrom(const module_list& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:pb.monitor.module_list)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  mid_clients_.MergeFrom(from.mid_clients_);
  if (from.clients_size() != 0) {
    set_clients_size(from.clients_size());
  }
  if (from.type_clients_size() != 0) {
    set_type_clients_size(from.type_clients_size());
  }
}

void module_list::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:pb.monitor.module_list)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void module_list::CopyFrom(const module_list& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:pb.monitor.module_list)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool module_list::IsInitialized() const {
  return true;
}

void module_list::Swap(module_list* other) {
  if (other == this) return;
  InternalSwap(other);
}
void module_list::InternalSwap(module_list* other) {
  using std::swap;
  CastToBase(&mid_clients_)->InternalSwap(CastToBase(&other->mid_clients_));
  swap(clients_size_, other->clients_size_);
  swap(type_clients_size_, other->type_clients_size_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata module_list::GetMetadata() const {
  protobuf_monitor_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_monitor_2eproto::file_level_metadata[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace monitor
}  // namespace pb
namespace google {
namespace protobuf {
template<> GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::pb::monitor::cmd* Arena::CreateMaybeMessage< ::pb::monitor::cmd >(Arena* arena) {
  return Arena::CreateInternal< ::pb::monitor::cmd >(arena);
}
template<> GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::pb::monitor::module_list* Arena::CreateMaybeMessage< ::pb::monitor::module_list >(Arena* arena) {
  return Arena::CreateInternal< ::pb::monitor::module_list >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
