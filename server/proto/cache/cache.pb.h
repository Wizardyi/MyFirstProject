// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: cache.proto

#ifndef PROTOBUF_cache_2eproto__INCLUDED
#define PROTOBUF_cache_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace cacheproto {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_cache_2eproto();
void protobuf_AssignDesc_cache_2eproto();
void protobuf_ShutdownFile_cache_2eproto();

class MessageType;
class OCCheckLive;

enum MessageType_Type {
  MessageType_Type_StartCmd = 0,
  MessageType_Type_OCStartCmd = 2000,
  MessageType_Type_OCCheckLive = 2001,
  MessageType_Type_OCSEndCmd = 2999,
  MessageType_Type_MessageType_Type_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  MessageType_Type_MessageType_Type_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool MessageType_Type_IsValid(int value);
const MessageType_Type MessageType_Type_Type_MIN = MessageType_Type_StartCmd;
const MessageType_Type MessageType_Type_Type_MAX = MessageType_Type_OCSEndCmd;
const int MessageType_Type_Type_ARRAYSIZE = MessageType_Type_Type_MAX + 1;

const ::google::protobuf::EnumDescriptor* MessageType_Type_descriptor();
inline const ::std::string& MessageType_Type_Name(MessageType_Type value) {
  return ::google::protobuf::internal::NameOfEnum(
    MessageType_Type_descriptor(), value);
}
inline bool MessageType_Type_Parse(
    const ::std::string& name, MessageType_Type* value) {
  return ::google::protobuf::internal::ParseNamedEnum<MessageType_Type>(
    MessageType_Type_descriptor(), name, value);
}
// ===================================================================

class MessageType : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:cacheproto.MessageType) */ {
 public:
  MessageType();
  virtual ~MessageType();

  MessageType(const MessageType& from);

  inline MessageType& operator=(const MessageType& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const MessageType& default_instance();

  void Swap(MessageType* other);

  // implements Message ----------------------------------------------

  inline MessageType* New() const { return New(NULL); }

  MessageType* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MessageType& from);
  void MergeFrom(const MessageType& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(MessageType* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  typedef MessageType_Type Type;
  static const Type StartCmd =
    MessageType_Type_StartCmd;
  static const Type OCStartCmd =
    MessageType_Type_OCStartCmd;
  static const Type OCCheckLive =
    MessageType_Type_OCCheckLive;
  static const Type OCSEndCmd =
    MessageType_Type_OCSEndCmd;
  static inline bool Type_IsValid(int value) {
    return MessageType_Type_IsValid(value);
  }
  static const Type Type_MIN =
    MessageType_Type_Type_MIN;
  static const Type Type_MAX =
    MessageType_Type_Type_MAX;
  static const int Type_ARRAYSIZE =
    MessageType_Type_Type_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Type_descriptor() {
    return MessageType_Type_descriptor();
  }
  static inline const ::std::string& Type_Name(Type value) {
    return MessageType_Type_Name(value);
  }
  static inline bool Type_Parse(const ::std::string& name,
      Type* value) {
    return MessageType_Type_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:cacheproto.MessageType)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_cache_2eproto();
  friend void protobuf_AssignDesc_cache_2eproto();
  friend void protobuf_ShutdownFile_cache_2eproto();

  void InitAsDefaultInstance();
  static MessageType* default_instance_;
};
// -------------------------------------------------------------------

class OCCheckLive : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:cacheproto.OCCheckLive) */ {
 public:
  OCCheckLive();
  virtual ~OCCheckLive();

  OCCheckLive(const OCCheckLive& from);

  inline OCCheckLive& operator=(const OCCheckLive& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const OCCheckLive& default_instance();

  void Swap(OCCheckLive* other);

  // implements Message ----------------------------------------------

  inline OCCheckLive* New() const { return New(NULL); }

  OCCheckLive* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const OCCheckLive& from);
  void MergeFrom(const OCCheckLive& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(OCCheckLive* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional uint32 id = 1;
  void clear_id();
  static const int kIdFieldNumber = 1;
  ::google::protobuf::uint32 id() const;
  void set_id(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:cacheproto.OCCheckLive)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::uint32 id_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_cache_2eproto();
  friend void protobuf_AssignDesc_cache_2eproto();
  friend void protobuf_ShutdownFile_cache_2eproto();

  void InitAsDefaultInstance();
  static OCCheckLive* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// MessageType

// -------------------------------------------------------------------

// OCCheckLive

// optional uint32 id = 1;
inline void OCCheckLive::clear_id() {
  id_ = 0u;
}
inline ::google::protobuf::uint32 OCCheckLive::id() const {
  // @@protoc_insertion_point(field_get:cacheproto.OCCheckLive.id)
  return id_;
}
inline void OCCheckLive::set_id(::google::protobuf::uint32 value) {
  
  id_ = value;
  // @@protoc_insertion_point(field_set:cacheproto.OCCheckLive.id)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace cacheproto

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::cacheproto::MessageType_Type> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::cacheproto::MessageType_Type>() {
  return ::cacheproto::MessageType_Type_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_cache_2eproto__INCLUDED