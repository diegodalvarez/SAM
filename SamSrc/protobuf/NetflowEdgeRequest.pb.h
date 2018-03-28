// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: NetflowEdgeRequest.proto

#ifndef PROTOBUF_NetflowEdgeRequest_2eproto__INCLUDED
#define PROTOBUF_NetflowEdgeRequest_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3005001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace protobuf_NetflowEdgeRequest_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[2];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
void InitDefaultsNetflowEdgeRequest_SimpleEdgeConditionImpl();
void InitDefaultsNetflowEdgeRequest_SimpleEdgeCondition();
void InitDefaultsNetflowEdgeRequestImpl();
void InitDefaultsNetflowEdgeRequest();
inline void InitDefaults() {
  InitDefaultsNetflowEdgeRequest_SimpleEdgeCondition();
  InitDefaultsNetflowEdgeRequest();
}
}  // namespace protobuf_NetflowEdgeRequest_2eproto
namespace sam {
class NetflowEdgeRequest;
class NetflowEdgeRequestDefaultTypeInternal;
extern NetflowEdgeRequestDefaultTypeInternal _NetflowEdgeRequest_default_instance_;
class NetflowEdgeRequest_SimpleEdgeCondition;
class NetflowEdgeRequest_SimpleEdgeConditionDefaultTypeInternal;
extern NetflowEdgeRequest_SimpleEdgeConditionDefaultTypeInternal _NetflowEdgeRequest_SimpleEdgeCondition_default_instance_;
}  // namespace sam
namespace sam {

// ===================================================================

class NetflowEdgeRequest_SimpleEdgeCondition : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:sam.NetflowEdgeRequest.SimpleEdgeCondition) */ {
 public:
  NetflowEdgeRequest_SimpleEdgeCondition();
  virtual ~NetflowEdgeRequest_SimpleEdgeCondition();

  NetflowEdgeRequest_SimpleEdgeCondition(const NetflowEdgeRequest_SimpleEdgeCondition& from);

  inline NetflowEdgeRequest_SimpleEdgeCondition& operator=(const NetflowEdgeRequest_SimpleEdgeCondition& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  NetflowEdgeRequest_SimpleEdgeCondition(NetflowEdgeRequest_SimpleEdgeCondition&& from) noexcept
    : NetflowEdgeRequest_SimpleEdgeCondition() {
    *this = ::std::move(from);
  }

  inline NetflowEdgeRequest_SimpleEdgeCondition& operator=(NetflowEdgeRequest_SimpleEdgeCondition&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const NetflowEdgeRequest_SimpleEdgeCondition& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const NetflowEdgeRequest_SimpleEdgeCondition* internal_default_instance() {
    return reinterpret_cast<const NetflowEdgeRequest_SimpleEdgeCondition*>(
               &_NetflowEdgeRequest_SimpleEdgeCondition_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(NetflowEdgeRequest_SimpleEdgeCondition* other);
  friend void swap(NetflowEdgeRequest_SimpleEdgeCondition& a, NetflowEdgeRequest_SimpleEdgeCondition& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline NetflowEdgeRequest_SimpleEdgeCondition* New() const PROTOBUF_FINAL { return New(NULL); }

  NetflowEdgeRequest_SimpleEdgeCondition* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const NetflowEdgeRequest_SimpleEdgeCondition& from);
  void MergeFrom(const NetflowEdgeRequest_SimpleEdgeCondition& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(NetflowEdgeRequest_SimpleEdgeCondition* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string field = 1;
  void clear_field();
  static const int kFieldFieldNumber = 1;
  const ::std::string& field() const;
  void set_field(const ::std::string& value);
  #if LANG_CXX11
  void set_field(::std::string&& value);
  #endif
  void set_field(const char* value);
  void set_field(const char* value, size_t size);
  ::std::string* mutable_field();
  ::std::string* release_field();
  void set_allocated_field(::std::string* field);

  // string operator = 2;
  void clear_operator_();
  static const int kOperatorFieldNumber = 2;
  const ::std::string& operator_() const;
  void set_operator_(const ::std::string& value);
  #if LANG_CXX11
  void set_operator_(::std::string&& value);
  #endif
  void set_operator_(const char* value);
  void set_operator_(const char* value, size_t size);
  ::std::string* mutable_operator_();
  ::std::string* release_operator_();
  void set_allocated_operator_(::std::string* operator_);

  // int32 rside = 3;
  void clear_rside();
  static const int kRsideFieldNumber = 3;
  ::google::protobuf::int32 rside() const;
  void set_rside(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:sam.NetflowEdgeRequest.SimpleEdgeCondition)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr field_;
  ::google::protobuf::internal::ArenaStringPtr operator__;
  ::google::protobuf::int32 rside_;
  mutable int _cached_size_;
  friend struct ::protobuf_NetflowEdgeRequest_2eproto::TableStruct;
  friend void ::protobuf_NetflowEdgeRequest_2eproto::InitDefaultsNetflowEdgeRequest_SimpleEdgeConditionImpl();
};
// -------------------------------------------------------------------

class NetflowEdgeRequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:sam.NetflowEdgeRequest) */ {
 public:
  NetflowEdgeRequest();
  virtual ~NetflowEdgeRequest();

  NetflowEdgeRequest(const NetflowEdgeRequest& from);

  inline NetflowEdgeRequest& operator=(const NetflowEdgeRequest& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  NetflowEdgeRequest(NetflowEdgeRequest&& from) noexcept
    : NetflowEdgeRequest() {
    *this = ::std::move(from);
  }

  inline NetflowEdgeRequest& operator=(NetflowEdgeRequest&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const NetflowEdgeRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const NetflowEdgeRequest* internal_default_instance() {
    return reinterpret_cast<const NetflowEdgeRequest*>(
               &_NetflowEdgeRequest_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(NetflowEdgeRequest* other);
  friend void swap(NetflowEdgeRequest& a, NetflowEdgeRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline NetflowEdgeRequest* New() const PROTOBUF_FINAL { return New(NULL); }

  NetflowEdgeRequest* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const NetflowEdgeRequest& from);
  void MergeFrom(const NetflowEdgeRequest& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(NetflowEdgeRequest* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  typedef NetflowEdgeRequest_SimpleEdgeCondition SimpleEdgeCondition;

  // accessors -------------------------------------------------------

  // repeated .sam.NetflowEdgeRequest.SimpleEdgeCondition conditions = 6;
  int conditions_size() const;
  void clear_conditions();
  static const int kConditionsFieldNumber = 6;
  const ::sam::NetflowEdgeRequest_SimpleEdgeCondition& conditions(int index) const;
  ::sam::NetflowEdgeRequest_SimpleEdgeCondition* mutable_conditions(int index);
  ::sam::NetflowEdgeRequest_SimpleEdgeCondition* add_conditions();
  ::google::protobuf::RepeatedPtrField< ::sam::NetflowEdgeRequest_SimpleEdgeCondition >*
      mutable_conditions();
  const ::google::protobuf::RepeatedPtrField< ::sam::NetflowEdgeRequest_SimpleEdgeCondition >&
      conditions() const;

  // string sourceIP = 1;
  void clear_sourceip();
  static const int kSourceIPFieldNumber = 1;
  const ::std::string& sourceip() const;
  void set_sourceip(const ::std::string& value);
  #if LANG_CXX11
  void set_sourceip(::std::string&& value);
  #endif
  void set_sourceip(const char* value);
  void set_sourceip(const char* value, size_t size);
  ::std::string* mutable_sourceip();
  ::std::string* release_sourceip();
  void set_allocated_sourceip(::std::string* sourceip);

  // string destIP = 2;
  void clear_destip();
  static const int kDestIPFieldNumber = 2;
  const ::std::string& destip() const;
  void set_destip(const ::std::string& value);
  #if LANG_CXX11
  void set_destip(::std::string&& value);
  #endif
  void set_destip(const char* value);
  void set_destip(const char* value, size_t size);
  ::std::string* mutable_destip();
  ::std::string* release_destip();
  void set_allocated_destip(::std::string* destip);

  // double startTime = 3;
  void clear_starttime();
  static const int kStartTimeFieldNumber = 3;
  double starttime() const;
  void set_starttime(double value);

  // double stopTime = 4;
  void clear_stoptime();
  static const int kStopTimeFieldNumber = 4;
  double stoptime() const;
  void set_stoptime(double value);

  // uint32 returnNode = 5;
  void clear_returnnode();
  static const int kReturnNodeFieldNumber = 5;
  ::google::protobuf::uint32 returnnode() const;
  void set_returnnode(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:sam.NetflowEdgeRequest)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::sam::NetflowEdgeRequest_SimpleEdgeCondition > conditions_;
  ::google::protobuf::internal::ArenaStringPtr sourceip_;
  ::google::protobuf::internal::ArenaStringPtr destip_;
  double starttime_;
  double stoptime_;
  ::google::protobuf::uint32 returnnode_;
  mutable int _cached_size_;
  friend struct ::protobuf_NetflowEdgeRequest_2eproto::TableStruct;
  friend void ::protobuf_NetflowEdgeRequest_2eproto::InitDefaultsNetflowEdgeRequestImpl();
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// NetflowEdgeRequest_SimpleEdgeCondition

// string field = 1;
inline void NetflowEdgeRequest_SimpleEdgeCondition::clear_field() {
  field_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& NetflowEdgeRequest_SimpleEdgeCondition::field() const {
  // @@protoc_insertion_point(field_get:sam.NetflowEdgeRequest.SimpleEdgeCondition.field)
  return field_.GetNoArena();
}
inline void NetflowEdgeRequest_SimpleEdgeCondition::set_field(const ::std::string& value) {
  
  field_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:sam.NetflowEdgeRequest.SimpleEdgeCondition.field)
}
#if LANG_CXX11
inline void NetflowEdgeRequest_SimpleEdgeCondition::set_field(::std::string&& value) {
  
  field_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:sam.NetflowEdgeRequest.SimpleEdgeCondition.field)
}
#endif
inline void NetflowEdgeRequest_SimpleEdgeCondition::set_field(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  field_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:sam.NetflowEdgeRequest.SimpleEdgeCondition.field)
}
inline void NetflowEdgeRequest_SimpleEdgeCondition::set_field(const char* value, size_t size) {
  
  field_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:sam.NetflowEdgeRequest.SimpleEdgeCondition.field)
}
inline ::std::string* NetflowEdgeRequest_SimpleEdgeCondition::mutable_field() {
  
  // @@protoc_insertion_point(field_mutable:sam.NetflowEdgeRequest.SimpleEdgeCondition.field)
  return field_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* NetflowEdgeRequest_SimpleEdgeCondition::release_field() {
  // @@protoc_insertion_point(field_release:sam.NetflowEdgeRequest.SimpleEdgeCondition.field)
  
  return field_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void NetflowEdgeRequest_SimpleEdgeCondition::set_allocated_field(::std::string* field) {
  if (field != NULL) {
    
  } else {
    
  }
  field_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), field);
  // @@protoc_insertion_point(field_set_allocated:sam.NetflowEdgeRequest.SimpleEdgeCondition.field)
}

// string operator = 2;
inline void NetflowEdgeRequest_SimpleEdgeCondition::clear_operator_() {
  operator__.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& NetflowEdgeRequest_SimpleEdgeCondition::operator_() const {
  // @@protoc_insertion_point(field_get:sam.NetflowEdgeRequest.SimpleEdgeCondition.operator)
  return operator__.GetNoArena();
}
inline void NetflowEdgeRequest_SimpleEdgeCondition::set_operator_(const ::std::string& value) {
  
  operator__.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:sam.NetflowEdgeRequest.SimpleEdgeCondition.operator)
}
#if LANG_CXX11
inline void NetflowEdgeRequest_SimpleEdgeCondition::set_operator_(::std::string&& value) {
  
  operator__.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:sam.NetflowEdgeRequest.SimpleEdgeCondition.operator)
}
#endif
inline void NetflowEdgeRequest_SimpleEdgeCondition::set_operator_(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  operator__.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:sam.NetflowEdgeRequest.SimpleEdgeCondition.operator)
}
inline void NetflowEdgeRequest_SimpleEdgeCondition::set_operator_(const char* value, size_t size) {
  
  operator__.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:sam.NetflowEdgeRequest.SimpleEdgeCondition.operator)
}
inline ::std::string* NetflowEdgeRequest_SimpleEdgeCondition::mutable_operator_() {
  
  // @@protoc_insertion_point(field_mutable:sam.NetflowEdgeRequest.SimpleEdgeCondition.operator)
  return operator__.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* NetflowEdgeRequest_SimpleEdgeCondition::release_operator_() {
  // @@protoc_insertion_point(field_release:sam.NetflowEdgeRequest.SimpleEdgeCondition.operator)
  
  return operator__.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void NetflowEdgeRequest_SimpleEdgeCondition::set_allocated_operator_(::std::string* operator_) {
  if (operator_ != NULL) {
    
  } else {
    
  }
  operator__.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), operator_);
  // @@protoc_insertion_point(field_set_allocated:sam.NetflowEdgeRequest.SimpleEdgeCondition.operator)
}

// int32 rside = 3;
inline void NetflowEdgeRequest_SimpleEdgeCondition::clear_rside() {
  rside_ = 0;
}
inline ::google::protobuf::int32 NetflowEdgeRequest_SimpleEdgeCondition::rside() const {
  // @@protoc_insertion_point(field_get:sam.NetflowEdgeRequest.SimpleEdgeCondition.rside)
  return rside_;
}
inline void NetflowEdgeRequest_SimpleEdgeCondition::set_rside(::google::protobuf::int32 value) {
  
  rside_ = value;
  // @@protoc_insertion_point(field_set:sam.NetflowEdgeRequest.SimpleEdgeCondition.rside)
}

// -------------------------------------------------------------------

// NetflowEdgeRequest

// string sourceIP = 1;
inline void NetflowEdgeRequest::clear_sourceip() {
  sourceip_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& NetflowEdgeRequest::sourceip() const {
  // @@protoc_insertion_point(field_get:sam.NetflowEdgeRequest.sourceIP)
  return sourceip_.GetNoArena();
}
inline void NetflowEdgeRequest::set_sourceip(const ::std::string& value) {
  
  sourceip_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:sam.NetflowEdgeRequest.sourceIP)
}
#if LANG_CXX11
inline void NetflowEdgeRequest::set_sourceip(::std::string&& value) {
  
  sourceip_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:sam.NetflowEdgeRequest.sourceIP)
}
#endif
inline void NetflowEdgeRequest::set_sourceip(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  sourceip_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:sam.NetflowEdgeRequest.sourceIP)
}
inline void NetflowEdgeRequest::set_sourceip(const char* value, size_t size) {
  
  sourceip_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:sam.NetflowEdgeRequest.sourceIP)
}
inline ::std::string* NetflowEdgeRequest::mutable_sourceip() {
  
  // @@protoc_insertion_point(field_mutable:sam.NetflowEdgeRequest.sourceIP)
  return sourceip_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* NetflowEdgeRequest::release_sourceip() {
  // @@protoc_insertion_point(field_release:sam.NetflowEdgeRequest.sourceIP)
  
  return sourceip_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void NetflowEdgeRequest::set_allocated_sourceip(::std::string* sourceip) {
  if (sourceip != NULL) {
    
  } else {
    
  }
  sourceip_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), sourceip);
  // @@protoc_insertion_point(field_set_allocated:sam.NetflowEdgeRequest.sourceIP)
}

// string destIP = 2;
inline void NetflowEdgeRequest::clear_destip() {
  destip_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& NetflowEdgeRequest::destip() const {
  // @@protoc_insertion_point(field_get:sam.NetflowEdgeRequest.destIP)
  return destip_.GetNoArena();
}
inline void NetflowEdgeRequest::set_destip(const ::std::string& value) {
  
  destip_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:sam.NetflowEdgeRequest.destIP)
}
#if LANG_CXX11
inline void NetflowEdgeRequest::set_destip(::std::string&& value) {
  
  destip_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:sam.NetflowEdgeRequest.destIP)
}
#endif
inline void NetflowEdgeRequest::set_destip(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  destip_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:sam.NetflowEdgeRequest.destIP)
}
inline void NetflowEdgeRequest::set_destip(const char* value, size_t size) {
  
  destip_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:sam.NetflowEdgeRequest.destIP)
}
inline ::std::string* NetflowEdgeRequest::mutable_destip() {
  
  // @@protoc_insertion_point(field_mutable:sam.NetflowEdgeRequest.destIP)
  return destip_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* NetflowEdgeRequest::release_destip() {
  // @@protoc_insertion_point(field_release:sam.NetflowEdgeRequest.destIP)
  
  return destip_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void NetflowEdgeRequest::set_allocated_destip(::std::string* destip) {
  if (destip != NULL) {
    
  } else {
    
  }
  destip_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), destip);
  // @@protoc_insertion_point(field_set_allocated:sam.NetflowEdgeRequest.destIP)
}

// double startTime = 3;
inline void NetflowEdgeRequest::clear_starttime() {
  starttime_ = 0;
}
inline double NetflowEdgeRequest::starttime() const {
  // @@protoc_insertion_point(field_get:sam.NetflowEdgeRequest.startTime)
  return starttime_;
}
inline void NetflowEdgeRequest::set_starttime(double value) {
  
  starttime_ = value;
  // @@protoc_insertion_point(field_set:sam.NetflowEdgeRequest.startTime)
}

// double stopTime = 4;
inline void NetflowEdgeRequest::clear_stoptime() {
  stoptime_ = 0;
}
inline double NetflowEdgeRequest::stoptime() const {
  // @@protoc_insertion_point(field_get:sam.NetflowEdgeRequest.stopTime)
  return stoptime_;
}
inline void NetflowEdgeRequest::set_stoptime(double value) {
  
  stoptime_ = value;
  // @@protoc_insertion_point(field_set:sam.NetflowEdgeRequest.stopTime)
}

// uint32 returnNode = 5;
inline void NetflowEdgeRequest::clear_returnnode() {
  returnnode_ = 0u;
}
inline ::google::protobuf::uint32 NetflowEdgeRequest::returnnode() const {
  // @@protoc_insertion_point(field_get:sam.NetflowEdgeRequest.returnNode)
  return returnnode_;
}
inline void NetflowEdgeRequest::set_returnnode(::google::protobuf::uint32 value) {
  
  returnnode_ = value;
  // @@protoc_insertion_point(field_set:sam.NetflowEdgeRequest.returnNode)
}

// repeated .sam.NetflowEdgeRequest.SimpleEdgeCondition conditions = 6;
inline int NetflowEdgeRequest::conditions_size() const {
  return conditions_.size();
}
inline void NetflowEdgeRequest::clear_conditions() {
  conditions_.Clear();
}
inline const ::sam::NetflowEdgeRequest_SimpleEdgeCondition& NetflowEdgeRequest::conditions(int index) const {
  // @@protoc_insertion_point(field_get:sam.NetflowEdgeRequest.conditions)
  return conditions_.Get(index);
}
inline ::sam::NetflowEdgeRequest_SimpleEdgeCondition* NetflowEdgeRequest::mutable_conditions(int index) {
  // @@protoc_insertion_point(field_mutable:sam.NetflowEdgeRequest.conditions)
  return conditions_.Mutable(index);
}
inline ::sam::NetflowEdgeRequest_SimpleEdgeCondition* NetflowEdgeRequest::add_conditions() {
  // @@protoc_insertion_point(field_add:sam.NetflowEdgeRequest.conditions)
  return conditions_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::sam::NetflowEdgeRequest_SimpleEdgeCondition >*
NetflowEdgeRequest::mutable_conditions() {
  // @@protoc_insertion_point(field_mutable_list:sam.NetflowEdgeRequest.conditions)
  return &conditions_;
}
inline const ::google::protobuf::RepeatedPtrField< ::sam::NetflowEdgeRequest_SimpleEdgeCondition >&
NetflowEdgeRequest::conditions() const {
  // @@protoc_insertion_point(field_list:sam.NetflowEdgeRequest.conditions)
  return conditions_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace sam

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_NetflowEdgeRequest_2eproto__INCLUDED
