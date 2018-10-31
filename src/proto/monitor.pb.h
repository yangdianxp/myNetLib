// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: monitor.proto

#ifndef PROTOBUF_INCLUDED_monitor_2eproto
#define PROTOBUF_INCLUDED_monitor_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_monitor_2eproto 

namespace protobuf_monitor_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_monitor_2eproto
namespace pb {
namespace monitor {
class cmd;
class cmdDefaultTypeInternal;
extern cmdDefaultTypeInternal _cmd_default_instance_;
}  // namespace monitor
}  // namespace pb
namespace google {
namespace protobuf {
template<> ::pb::monitor::cmd* Arena::CreateMaybeMessage<::pb::monitor::cmd>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace pb {
namespace monitor {

// ===================================================================

class cmd : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:pb.monitor.cmd) */ {
 public:
  cmd();
  virtual ~cmd();

  cmd(const cmd& from);

  inline cmd& operator=(const cmd& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  cmd(cmd&& from) noexcept
    : cmd() {
    *this = ::std::move(from);
  }

  inline cmd& operator=(cmd&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const cmd& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const cmd* internal_default_instance() {
    return reinterpret_cast<const cmd*>(
               &_cmd_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(cmd* other);
  friend void swap(cmd& a, cmd& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline cmd* New() const final {
    return CreateMaybeMessage<cmd>(NULL);
  }

  cmd* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<cmd>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const cmd& from);
  void MergeFrom(const cmd& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(cmd* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string content = 1;
  void clear_content();
  static const int kContentFieldNumber = 1;
  const ::std::string& content() const;
  void set_content(const ::std::string& value);
  #if LANG_CXX11
  void set_content(::std::string&& value);
  #endif
  void set_content(const char* value);
  void set_content(const char* value, size_t size);
  ::std::string* mutable_content();
  ::std::string* release_content();
  void set_allocated_content(::std::string* content);

  // @@protoc_insertion_point(class_scope:pb.monitor.cmd)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr content_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_monitor_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// cmd

// string content = 1;
inline void cmd::clear_content() {
  content_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& cmd::content() const {
  // @@protoc_insertion_point(field_get:pb.monitor.cmd.content)
  return content_.GetNoArena();
}
inline void cmd::set_content(const ::std::string& value) {
  
  content_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:pb.monitor.cmd.content)
}
#if LANG_CXX11
inline void cmd::set_content(::std::string&& value) {
  
  content_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:pb.monitor.cmd.content)
}
#endif
inline void cmd::set_content(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  content_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:pb.monitor.cmd.content)
}
inline void cmd::set_content(const char* value, size_t size) {
  
  content_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:pb.monitor.cmd.content)
}
inline ::std::string* cmd::mutable_content() {
  
  // @@protoc_insertion_point(field_mutable:pb.monitor.cmd.content)
  return content_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* cmd::release_content() {
  // @@protoc_insertion_point(field_release:pb.monitor.cmd.content)
  
  return content_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void cmd::set_allocated_content(::std::string* content) {
  if (content != NULL) {
    
  } else {
    
  }
  content_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), content);
  // @@protoc_insertion_point(field_set_allocated:pb.monitor.cmd.content)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace monitor
}  // namespace pb

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_monitor_2eproto
