// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: gate.proto

#ifndef PROTOBUF_gate_2eproto__INCLUDED
#define PROTOBUF_gate_2eproto__INCLUDED

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

namespace gateproto {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_gate_2eproto();
void protobuf_AssignDesc_gate_2eproto();
void protobuf_ShutdownFile_gate_2eproto();

class BGBattleResultNotify;
class BattleResult;
class CGEnterGame;
class GCEnterGame;
class MessageType;
class PGPlayerTroopPos;

enum MessageType_Cmd {
  MessageType_Cmd_StartCmd = 0,
  MessageType_Cmd_CGStartCmd = 8000,
  MessageType_Cmd_CGEnterGame = 8001,
  MessageType_Cmd_BGBattleResultNotify = 8002,
  MessageType_Cmd_PGPlayerTroopPos = 8003,
  MessageType_Cmd_CGEndCmd = 8999,
  MessageType_Cmd_MessageType_Cmd_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  MessageType_Cmd_MessageType_Cmd_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool MessageType_Cmd_IsValid(int value);
const MessageType_Cmd MessageType_Cmd_Cmd_MIN = MessageType_Cmd_StartCmd;
const MessageType_Cmd MessageType_Cmd_Cmd_MAX = MessageType_Cmd_CGEndCmd;
const int MessageType_Cmd_Cmd_ARRAYSIZE = MessageType_Cmd_Cmd_MAX + 1;

const ::google::protobuf::EnumDescriptor* MessageType_Cmd_descriptor();
inline const ::std::string& MessageType_Cmd_Name(MessageType_Cmd value) {
  return ::google::protobuf::internal::NameOfEnum(
    MessageType_Cmd_descriptor(), value);
}
inline bool MessageType_Cmd_Parse(
    const ::std::string& name, MessageType_Cmd* value) {
  return ::google::protobuf::internal::ParseNamedEnum<MessageType_Cmd>(
    MessageType_Cmd_descriptor(), name, value);
}
// ===================================================================

class MessageType : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:gateproto.MessageType) */ {
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

  typedef MessageType_Cmd Cmd;
  static const Cmd StartCmd =
    MessageType_Cmd_StartCmd;
  static const Cmd CGStartCmd =
    MessageType_Cmd_CGStartCmd;
  static const Cmd CGEnterGame =
    MessageType_Cmd_CGEnterGame;
  static const Cmd BGBattleResultNotify =
    MessageType_Cmd_BGBattleResultNotify;
  static const Cmd PGPlayerTroopPos =
    MessageType_Cmd_PGPlayerTroopPos;
  static const Cmd CGEndCmd =
    MessageType_Cmd_CGEndCmd;
  static inline bool Cmd_IsValid(int value) {
    return MessageType_Cmd_IsValid(value);
  }
  static const Cmd Cmd_MIN =
    MessageType_Cmd_Cmd_MIN;
  static const Cmd Cmd_MAX =
    MessageType_Cmd_Cmd_MAX;
  static const int Cmd_ARRAYSIZE =
    MessageType_Cmd_Cmd_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Cmd_descriptor() {
    return MessageType_Cmd_descriptor();
  }
  static inline const ::std::string& Cmd_Name(Cmd value) {
    return MessageType_Cmd_Name(value);
  }
  static inline bool Cmd_Parse(const ::std::string& name,
      Cmd* value) {
    return MessageType_Cmd_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:gateproto.MessageType)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_gate_2eproto();
  friend void protobuf_AssignDesc_gate_2eproto();
  friend void protobuf_ShutdownFile_gate_2eproto();

  void InitAsDefaultInstance();
  static MessageType* default_instance_;
};
// -------------------------------------------------------------------

class CGEnterGame : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:gateproto.CGEnterGame) */ {
 public:
  CGEnterGame();
  virtual ~CGEnterGame();

  CGEnterGame(const CGEnterGame& from);

  inline CGEnterGame& operator=(const CGEnterGame& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const CGEnterGame& default_instance();

  void Swap(CGEnterGame* other);

  // implements Message ----------------------------------------------

  inline CGEnterGame* New() const { return New(NULL); }

  CGEnterGame* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const CGEnterGame& from);
  void MergeFrom(const CGEnterGame& from);
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
  void InternalSwap(CGEnterGame* other);
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

  // @@protoc_insertion_point(class_scope:gateproto.CGEnterGame)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::uint32 id_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_gate_2eproto();
  friend void protobuf_AssignDesc_gate_2eproto();
  friend void protobuf_ShutdownFile_gate_2eproto();

  void InitAsDefaultInstance();
  static CGEnterGame* default_instance_;
};
// -------------------------------------------------------------------

class GCEnterGame : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:gateproto.GCEnterGame) */ {
 public:
  GCEnterGame();
  virtual ~GCEnterGame();

  GCEnterGame(const GCEnterGame& from);

  inline GCEnterGame& operator=(const GCEnterGame& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const GCEnterGame& default_instance();

  void Swap(GCEnterGame* other);

  // implements Message ----------------------------------------------

  inline GCEnterGame* New() const { return New(NULL); }

  GCEnterGame* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GCEnterGame& from);
  void MergeFrom(const GCEnterGame& from);
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
  void InternalSwap(GCEnterGame* other);
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

  // @@protoc_insertion_point(class_scope:gateproto.GCEnterGame)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_gate_2eproto();
  friend void protobuf_AssignDesc_gate_2eproto();
  friend void protobuf_ShutdownFile_gate_2eproto();

  void InitAsDefaultInstance();
  static GCEnterGame* default_instance_;
};
// -------------------------------------------------------------------

class BattleResult : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:gateproto.BattleResult) */ {
 public:
  BattleResult();
  virtual ~BattleResult();

  BattleResult(const BattleResult& from);

  inline BattleResult& operator=(const BattleResult& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const BattleResult& default_instance();

  void Swap(BattleResult* other);

  // implements Message ----------------------------------------------

  inline BattleResult* New() const { return New(NULL); }

  BattleResult* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const BattleResult& from);
  void MergeFrom(const BattleResult& from);
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
  void InternalSwap(BattleResult* other);
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

  // optional uint64 attack_id = 1;
  void clear_attack_id();
  static const int kAttackIdFieldNumber = 1;
  ::google::protobuf::uint64 attack_id() const;
  void set_attack_id(::google::protobuf::uint64 value);

  // optional uint64 be_attacked_id = 2;
  void clear_be_attacked_id();
  static const int kBeAttackedIdFieldNumber = 2;
  ::google::protobuf::uint64 be_attacked_id() const;
  void set_be_attacked_id(::google::protobuf::uint64 value);

  // optional float attack = 3;
  void clear_attack();
  static const int kAttackFieldNumber = 3;
  float attack() const;
  void set_attack(float value);

  // @@protoc_insertion_point(class_scope:gateproto.BattleResult)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::uint64 attack_id_;
  ::google::protobuf::uint64 be_attacked_id_;
  float attack_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_gate_2eproto();
  friend void protobuf_AssignDesc_gate_2eproto();
  friend void protobuf_ShutdownFile_gate_2eproto();

  void InitAsDefaultInstance();
  static BattleResult* default_instance_;
};
// -------------------------------------------------------------------

class BGBattleResultNotify : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:gateproto.BGBattleResultNotify) */ {
 public:
  BGBattleResultNotify();
  virtual ~BGBattleResultNotify();

  BGBattleResultNotify(const BGBattleResultNotify& from);

  inline BGBattleResultNotify& operator=(const BGBattleResultNotify& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const BGBattleResultNotify& default_instance();

  void Swap(BGBattleResultNotify* other);

  // implements Message ----------------------------------------------

  inline BGBattleResultNotify* New() const { return New(NULL); }

  BGBattleResultNotify* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const BGBattleResultNotify& from);
  void MergeFrom(const BGBattleResultNotify& from);
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
  void InternalSwap(BGBattleResultNotify* other);
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

  // repeated .gateproto.BattleResult result = 1;
  int result_size() const;
  void clear_result();
  static const int kResultFieldNumber = 1;
  const ::gateproto::BattleResult& result(int index) const;
  ::gateproto::BattleResult* mutable_result(int index);
  ::gateproto::BattleResult* add_result();
  ::google::protobuf::RepeatedPtrField< ::gateproto::BattleResult >*
      mutable_result();
  const ::google::protobuf::RepeatedPtrField< ::gateproto::BattleResult >&
      result() const;

  // @@protoc_insertion_point(class_scope:gateproto.BGBattleResultNotify)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::RepeatedPtrField< ::gateproto::BattleResult > result_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_gate_2eproto();
  friend void protobuf_AssignDesc_gate_2eproto();
  friend void protobuf_ShutdownFile_gate_2eproto();

  void InitAsDefaultInstance();
  static BGBattleResultNotify* default_instance_;
};
// -------------------------------------------------------------------

class PGPlayerTroopPos : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:gateproto.PGPlayerTroopPos) */ {
 public:
  PGPlayerTroopPos();
  virtual ~PGPlayerTroopPos();

  PGPlayerTroopPos(const PGPlayerTroopPos& from);

  inline PGPlayerTroopPos& operator=(const PGPlayerTroopPos& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const PGPlayerTroopPos& default_instance();

  void Swap(PGPlayerTroopPos* other);

  // implements Message ----------------------------------------------

  inline PGPlayerTroopPos* New() const { return New(NULL); }

  PGPlayerTroopPos* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PGPlayerTroopPos& from);
  void MergeFrom(const PGPlayerTroopPos& from);
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
  void InternalSwap(PGPlayerTroopPos* other);
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

  // optional uint64 troop_id = 1;
  void clear_troop_id();
  static const int kTroopIdFieldNumber = 1;
  ::google::protobuf::uint64 troop_id() const;
  void set_troop_id(::google::protobuf::uint64 value);

  // optional float pos_x = 2;
  void clear_pos_x();
  static const int kPosXFieldNumber = 2;
  float pos_x() const;
  void set_pos_x(float value);

  // optional float pos_y = 3;
  void clear_pos_y();
  static const int kPosYFieldNumber = 3;
  float pos_y() const;
  void set_pos_y(float value);

  // @@protoc_insertion_point(class_scope:gateproto.PGPlayerTroopPos)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::uint64 troop_id_;
  float pos_x_;
  float pos_y_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_gate_2eproto();
  friend void protobuf_AssignDesc_gate_2eproto();
  friend void protobuf_ShutdownFile_gate_2eproto();

  void InitAsDefaultInstance();
  static PGPlayerTroopPos* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// MessageType

// -------------------------------------------------------------------

// CGEnterGame

// optional uint32 id = 1;
inline void CGEnterGame::clear_id() {
  id_ = 0u;
}
inline ::google::protobuf::uint32 CGEnterGame::id() const {
  // @@protoc_insertion_point(field_get:gateproto.CGEnterGame.id)
  return id_;
}
inline void CGEnterGame::set_id(::google::protobuf::uint32 value) {
  
  id_ = value;
  // @@protoc_insertion_point(field_set:gateproto.CGEnterGame.id)
}

// -------------------------------------------------------------------

// GCEnterGame

// -------------------------------------------------------------------

// BattleResult

// optional uint64 attack_id = 1;
inline void BattleResult::clear_attack_id() {
  attack_id_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 BattleResult::attack_id() const {
  // @@protoc_insertion_point(field_get:gateproto.BattleResult.attack_id)
  return attack_id_;
}
inline void BattleResult::set_attack_id(::google::protobuf::uint64 value) {
  
  attack_id_ = value;
  // @@protoc_insertion_point(field_set:gateproto.BattleResult.attack_id)
}

// optional uint64 be_attacked_id = 2;
inline void BattleResult::clear_be_attacked_id() {
  be_attacked_id_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 BattleResult::be_attacked_id() const {
  // @@protoc_insertion_point(field_get:gateproto.BattleResult.be_attacked_id)
  return be_attacked_id_;
}
inline void BattleResult::set_be_attacked_id(::google::protobuf::uint64 value) {
  
  be_attacked_id_ = value;
  // @@protoc_insertion_point(field_set:gateproto.BattleResult.be_attacked_id)
}

// optional float attack = 3;
inline void BattleResult::clear_attack() {
  attack_ = 0;
}
inline float BattleResult::attack() const {
  // @@protoc_insertion_point(field_get:gateproto.BattleResult.attack)
  return attack_;
}
inline void BattleResult::set_attack(float value) {
  
  attack_ = value;
  // @@protoc_insertion_point(field_set:gateproto.BattleResult.attack)
}

// -------------------------------------------------------------------

// BGBattleResultNotify

// repeated .gateproto.BattleResult result = 1;
inline int BGBattleResultNotify::result_size() const {
  return result_.size();
}
inline void BGBattleResultNotify::clear_result() {
  result_.Clear();
}
inline const ::gateproto::BattleResult& BGBattleResultNotify::result(int index) const {
  // @@protoc_insertion_point(field_get:gateproto.BGBattleResultNotify.result)
  return result_.Get(index);
}
inline ::gateproto::BattleResult* BGBattleResultNotify::mutable_result(int index) {
  // @@protoc_insertion_point(field_mutable:gateproto.BGBattleResultNotify.result)
  return result_.Mutable(index);
}
inline ::gateproto::BattleResult* BGBattleResultNotify::add_result() {
  // @@protoc_insertion_point(field_add:gateproto.BGBattleResultNotify.result)
  return result_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::gateproto::BattleResult >*
BGBattleResultNotify::mutable_result() {
  // @@protoc_insertion_point(field_mutable_list:gateproto.BGBattleResultNotify.result)
  return &result_;
}
inline const ::google::protobuf::RepeatedPtrField< ::gateproto::BattleResult >&
BGBattleResultNotify::result() const {
  // @@protoc_insertion_point(field_list:gateproto.BGBattleResultNotify.result)
  return result_;
}

// -------------------------------------------------------------------

// PGPlayerTroopPos

// optional uint64 troop_id = 1;
inline void PGPlayerTroopPos::clear_troop_id() {
  troop_id_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 PGPlayerTroopPos::troop_id() const {
  // @@protoc_insertion_point(field_get:gateproto.PGPlayerTroopPos.troop_id)
  return troop_id_;
}
inline void PGPlayerTroopPos::set_troop_id(::google::protobuf::uint64 value) {
  
  troop_id_ = value;
  // @@protoc_insertion_point(field_set:gateproto.PGPlayerTroopPos.troop_id)
}

// optional float pos_x = 2;
inline void PGPlayerTroopPos::clear_pos_x() {
  pos_x_ = 0;
}
inline float PGPlayerTroopPos::pos_x() const {
  // @@protoc_insertion_point(field_get:gateproto.PGPlayerTroopPos.pos_x)
  return pos_x_;
}
inline void PGPlayerTroopPos::set_pos_x(float value) {
  
  pos_x_ = value;
  // @@protoc_insertion_point(field_set:gateproto.PGPlayerTroopPos.pos_x)
}

// optional float pos_y = 3;
inline void PGPlayerTroopPos::clear_pos_y() {
  pos_y_ = 0;
}
inline float PGPlayerTroopPos::pos_y() const {
  // @@protoc_insertion_point(field_get:gateproto.PGPlayerTroopPos.pos_y)
  return pos_y_;
}
inline void PGPlayerTroopPos::set_pos_y(float value) {
  
  pos_y_ = value;
  // @@protoc_insertion_point(field_set:gateproto.PGPlayerTroopPos.pos_y)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace gateproto

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::gateproto::MessageType_Cmd> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::gateproto::MessageType_Cmd>() {
  return ::gateproto::MessageType_Cmd_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_gate_2eproto__INCLUDED