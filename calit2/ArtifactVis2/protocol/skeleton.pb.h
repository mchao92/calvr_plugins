// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: protocol/skeleton.proto

#ifndef PROTOBUF_protocol_2fskeleton_2eproto__INCLUDED
#define PROTOBUF_protocol_2fskeleton_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

namespace RemoteKinect {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_protocol_2fskeleton_2eproto();
void protobuf_AssignDesc_protocol_2fskeleton_2eproto();
void protobuf_ShutdownFile_protocol_2fskeleton_2eproto();

class Skeleton;
class Skeleton_Joint;

enum Skeleton_Joint_Type {
  Skeleton_Joint_Type_HEAD = 1,
  Skeleton_Joint_Type_NECK = 2,
  Skeleton_Joint_Type_TORSO = 3,
  Skeleton_Joint_Type_WAIST = 4,
  Skeleton_Joint_Type_COLLAR_LEFT = 5,
  Skeleton_Joint_Type_SHOULDER_LEFT = 6,
  Skeleton_Joint_Type_ELBOW_LEFT = 7,
  Skeleton_Joint_Type_WRIST_LEFT = 8,
  Skeleton_Joint_Type_HAND_LEFT = 9,
  Skeleton_Joint_Type_FINGERTIP_LEFT = 10,
  Skeleton_Joint_Type_COLLAR_RIGHT = 11,
  Skeleton_Joint_Type_SHOULDER_RIGHT = 12,
  Skeleton_Joint_Type_ELBOW_RIGHT = 13,
  Skeleton_Joint_Type_WRIST_RIGHT = 14,
  Skeleton_Joint_Type_HAND_RIGHT = 15,
  Skeleton_Joint_Type_FINGERTIP_RIGHT = 16,
  Skeleton_Joint_Type_HIP_LEFT = 17,
  Skeleton_Joint_Type_KNEE_LEFT = 18,
  Skeleton_Joint_Type_ANKLE_LEFT = 19,
  Skeleton_Joint_Type_FOOT_LEFT = 20,
  Skeleton_Joint_Type_HIP_RIGHT = 21,
  Skeleton_Joint_Type_KNEE_RIGHT = 22,
  Skeleton_Joint_Type_ANKLE_RIGHT = 23,
  Skeleton_Joint_Type_FOOT_RIGHT = 24
};
bool Skeleton_Joint_Type_IsValid(int value);
const Skeleton_Joint_Type Skeleton_Joint_Type_Type_MIN = Skeleton_Joint_Type_HEAD;
const Skeleton_Joint_Type Skeleton_Joint_Type_Type_MAX = Skeleton_Joint_Type_FOOT_RIGHT;
const int Skeleton_Joint_Type_Type_ARRAYSIZE = Skeleton_Joint_Type_Type_MAX + 1;

const ::google::protobuf::EnumDescriptor* Skeleton_Joint_Type_descriptor();
inline const ::std::string& Skeleton_Joint_Type_Name(Skeleton_Joint_Type value) {
  return ::google::protobuf::internal::NameOfEnum(
    Skeleton_Joint_Type_descriptor(), value);
}
inline bool Skeleton_Joint_Type_Parse(
    const ::std::string& name, Skeleton_Joint_Type* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Skeleton_Joint_Type>(
    Skeleton_Joint_Type_descriptor(), name, value);
}
// ===================================================================

class Skeleton_Joint : public ::google::protobuf::Message {
 public:
  Skeleton_Joint();
  virtual ~Skeleton_Joint();
  
  Skeleton_Joint(const Skeleton_Joint& from);
  
  inline Skeleton_Joint& operator=(const Skeleton_Joint& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Skeleton_Joint& default_instance();
  
  void Swap(Skeleton_Joint* other);
  
  // implements Message ----------------------------------------------
  
  Skeleton_Joint* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Skeleton_Joint& from);
  void MergeFrom(const Skeleton_Joint& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  typedef Skeleton_Joint_Type Type;
  static const Type HEAD = Skeleton_Joint_Type_HEAD;
  static const Type NECK = Skeleton_Joint_Type_NECK;
  static const Type TORSO = Skeleton_Joint_Type_TORSO;
  static const Type WAIST = Skeleton_Joint_Type_WAIST;
  static const Type COLLAR_LEFT = Skeleton_Joint_Type_COLLAR_LEFT;
  static const Type SHOULDER_LEFT = Skeleton_Joint_Type_SHOULDER_LEFT;
  static const Type ELBOW_LEFT = Skeleton_Joint_Type_ELBOW_LEFT;
  static const Type WRIST_LEFT = Skeleton_Joint_Type_WRIST_LEFT;
  static const Type HAND_LEFT = Skeleton_Joint_Type_HAND_LEFT;
  static const Type FINGERTIP_LEFT = Skeleton_Joint_Type_FINGERTIP_LEFT;
  static const Type COLLAR_RIGHT = Skeleton_Joint_Type_COLLAR_RIGHT;
  static const Type SHOULDER_RIGHT = Skeleton_Joint_Type_SHOULDER_RIGHT;
  static const Type ELBOW_RIGHT = Skeleton_Joint_Type_ELBOW_RIGHT;
  static const Type WRIST_RIGHT = Skeleton_Joint_Type_WRIST_RIGHT;
  static const Type HAND_RIGHT = Skeleton_Joint_Type_HAND_RIGHT;
  static const Type FINGERTIP_RIGHT = Skeleton_Joint_Type_FINGERTIP_RIGHT;
  static const Type HIP_LEFT = Skeleton_Joint_Type_HIP_LEFT;
  static const Type KNEE_LEFT = Skeleton_Joint_Type_KNEE_LEFT;
  static const Type ANKLE_LEFT = Skeleton_Joint_Type_ANKLE_LEFT;
  static const Type FOOT_LEFT = Skeleton_Joint_Type_FOOT_LEFT;
  static const Type HIP_RIGHT = Skeleton_Joint_Type_HIP_RIGHT;
  static const Type KNEE_RIGHT = Skeleton_Joint_Type_KNEE_RIGHT;
  static const Type ANKLE_RIGHT = Skeleton_Joint_Type_ANKLE_RIGHT;
  static const Type FOOT_RIGHT = Skeleton_Joint_Type_FOOT_RIGHT;
  static inline bool Type_IsValid(int value) {
    return Skeleton_Joint_Type_IsValid(value);
  }
  static const Type Type_MIN =
    Skeleton_Joint_Type_Type_MIN;
  static const Type Type_MAX =
    Skeleton_Joint_Type_Type_MAX;
  static const int Type_ARRAYSIZE =
    Skeleton_Joint_Type_Type_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Type_descriptor() {
    return Skeleton_Joint_Type_descriptor();
  }
  static inline const ::std::string& Type_Name(Type value) {
    return Skeleton_Joint_Type_Name(value);
  }
  static inline bool Type_Parse(const ::std::string& name,
      Type* value) {
    return Skeleton_Joint_Type_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // required .RemoteKinect.Skeleton.Joint.Type type = 1;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 1;
  inline ::RemoteKinect::Skeleton_Joint_Type type() const;
  inline void set_type(::RemoteKinect::Skeleton_Joint_Type value);
  
  // required float x = 2;
  inline bool has_x() const;
  inline void clear_x();
  static const int kXFieldNumber = 2;
  inline float x() const;
  inline void set_x(float value);
  
  // required float y = 3;
  inline bool has_y() const;
  inline void clear_y();
  static const int kYFieldNumber = 3;
  inline float y() const;
  inline void set_y(float value);
  
  // required float z = 4;
  inline bool has_z() const;
  inline void clear_z();
  static const int kZFieldNumber = 4;
  inline float z() const;
  inline void set_z(float value);
  
  // optional float image_x = 9;
  inline bool has_image_x() const;
  inline void clear_image_x();
  static const int kImageXFieldNumber = 9;
  inline float image_x() const;
  inline void set_image_x(float value);
  
  // optional float image_y = 10;
  inline bool has_image_y() const;
  inline void clear_image_y();
  static const int kImageYFieldNumber = 10;
  inline float image_y() const;
  inline void set_image_y(float value);
  
  // optional float qw = 5;
  inline bool has_qw() const;
  inline void clear_qw();
  static const int kQwFieldNumber = 5;
  inline float qw() const;
  inline void set_qw(float value);
  
  // optional float qx = 6;
  inline bool has_qx() const;
  inline void clear_qx();
  static const int kQxFieldNumber = 6;
  inline float qx() const;
  inline void set_qx(float value);
  
  // optional float qy = 7;
  inline bool has_qy() const;
  inline void clear_qy();
  static const int kQyFieldNumber = 7;
  inline float qy() const;
  inline void set_qy(float value);
  
  // optional float qz = 8;
  inline bool has_qz() const;
  inline void clear_qz();
  static const int kQzFieldNumber = 8;
  inline float qz() const;
  inline void set_qz(float value);
  
  // @@protoc_insertion_point(class_scope:RemoteKinect.Skeleton.Joint)
 private:
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_x();
  inline void clear_has_x();
  inline void set_has_y();
  inline void clear_has_y();
  inline void set_has_z();
  inline void clear_has_z();
  inline void set_has_image_x();
  inline void clear_has_image_x();
  inline void set_has_image_y();
  inline void clear_has_image_y();
  inline void set_has_qw();
  inline void clear_has_qw();
  inline void set_has_qx();
  inline void clear_has_qx();
  inline void set_has_qy();
  inline void clear_has_qy();
  inline void set_has_qz();
  inline void clear_has_qz();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  int type_;
  float x_;
  float y_;
  float z_;
  float image_x_;
  float image_y_;
  float qw_;
  float qx_;
  float qy_;
  float qz_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(10 + 31) / 32];
  
  friend void  protobuf_AddDesc_protocol_2fskeleton_2eproto();
  friend void protobuf_AssignDesc_protocol_2fskeleton_2eproto();
  friend void protobuf_ShutdownFile_protocol_2fskeleton_2eproto();
  
  void InitAsDefaultInstance();
  static Skeleton_Joint* default_instance_;
};
// -------------------------------------------------------------------

class Skeleton : public ::google::protobuf::Message {
 public:
  Skeleton();
  virtual ~Skeleton();
  
  Skeleton(const Skeleton& from);
  
  inline Skeleton& operator=(const Skeleton& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Skeleton& default_instance();
  
  void Swap(Skeleton* other);
  
  // implements Message ----------------------------------------------
  
  Skeleton* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Skeleton& from);
  void MergeFrom(const Skeleton& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  typedef Skeleton_Joint Joint;
  
  // accessors -------------------------------------------------------
  
  // required string source_serial = 1;
  inline bool has_source_serial() const;
  inline void clear_source_serial();
  static const int kSourceSerialFieldNumber = 1;
  inline const ::std::string& source_serial() const;
  inline void set_source_serial(const ::std::string& value);
  inline void set_source_serial(const char* value);
  inline void set_source_serial(const char* value, size_t size);
  inline ::std::string* mutable_source_serial();
  inline ::std::string* release_source_serial();
  
  // required uint32 tick = 2;
  inline bool has_tick() const;
  inline void clear_tick();
  static const int kTickFieldNumber = 2;
  inline ::google::protobuf::uint32 tick() const;
  inline void set_tick(::google::protobuf::uint32 value);
  
  // required uint32 skeleton_id = 3;
  inline bool has_skeleton_id() const;
  inline void clear_skeleton_id();
  static const int kSkeletonIdFieldNumber = 3;
  inline ::google::protobuf::uint32 skeleton_id() const;
  inline void set_skeleton_id(::google::protobuf::uint32 value);
  
  // repeated .RemoteKinect.Skeleton.Joint joints = 4;
  inline int joints_size() const;
  inline void clear_joints();
  static const int kJointsFieldNumber = 4;
  inline const ::RemoteKinect::Skeleton_Joint& joints(int index) const;
  inline ::RemoteKinect::Skeleton_Joint* mutable_joints(int index);
  inline ::RemoteKinect::Skeleton_Joint* add_joints();
  inline const ::google::protobuf::RepeatedPtrField< ::RemoteKinect::Skeleton_Joint >&
      joints() const;
  inline ::google::protobuf::RepeatedPtrField< ::RemoteKinect::Skeleton_Joint >*
      mutable_joints();
  
  // @@protoc_insertion_point(class_scope:RemoteKinect.Skeleton)
 private:
  inline void set_has_source_serial();
  inline void clear_has_source_serial();
  inline void set_has_tick();
  inline void clear_has_tick();
  inline void set_has_skeleton_id();
  inline void clear_has_skeleton_id();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* source_serial_;
  ::google::protobuf::uint32 tick_;
  ::google::protobuf::uint32 skeleton_id_;
  ::google::protobuf::RepeatedPtrField< ::RemoteKinect::Skeleton_Joint > joints_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];
  
  friend void  protobuf_AddDesc_protocol_2fskeleton_2eproto();
  friend void protobuf_AssignDesc_protocol_2fskeleton_2eproto();
  friend void protobuf_ShutdownFile_protocol_2fskeleton_2eproto();
  
  void InitAsDefaultInstance();
  static Skeleton* default_instance_;
};
// ===================================================================


// ===================================================================

// Skeleton_Joint

// required .RemoteKinect.Skeleton.Joint.Type type = 1;
inline bool Skeleton_Joint::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Skeleton_Joint::set_has_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Skeleton_Joint::clear_has_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Skeleton_Joint::clear_type() {
  type_ = 1;
  clear_has_type();
}
inline ::RemoteKinect::Skeleton_Joint_Type Skeleton_Joint::type() const {
  return static_cast< ::RemoteKinect::Skeleton_Joint_Type >(type_);
}
inline void Skeleton_Joint::set_type(::RemoteKinect::Skeleton_Joint_Type value) {
  GOOGLE_DCHECK(::RemoteKinect::Skeleton_Joint_Type_IsValid(value));
  set_has_type();
  type_ = value;
}

// required float x = 2;
inline bool Skeleton_Joint::has_x() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Skeleton_Joint::set_has_x() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Skeleton_Joint::clear_has_x() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Skeleton_Joint::clear_x() {
  x_ = 0;
  clear_has_x();
}
inline float Skeleton_Joint::x() const {
  return x_;
}
inline void Skeleton_Joint::set_x(float value) {
  set_has_x();
  x_ = value;
}

// required float y = 3;
inline bool Skeleton_Joint::has_y() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Skeleton_Joint::set_has_y() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Skeleton_Joint::clear_has_y() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Skeleton_Joint::clear_y() {
  y_ = 0;
  clear_has_y();
}
inline float Skeleton_Joint::y() const {
  return y_;
}
inline void Skeleton_Joint::set_y(float value) {
  set_has_y();
  y_ = value;
}

// required float z = 4;
inline bool Skeleton_Joint::has_z() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Skeleton_Joint::set_has_z() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Skeleton_Joint::clear_has_z() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Skeleton_Joint::clear_z() {
  z_ = 0;
  clear_has_z();
}
inline float Skeleton_Joint::z() const {
  return z_;
}
inline void Skeleton_Joint::set_z(float value) {
  set_has_z();
  z_ = value;
}

// optional float image_x = 9;
inline bool Skeleton_Joint::has_image_x() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void Skeleton_Joint::set_has_image_x() {
  _has_bits_[0] |= 0x00000010u;
}
inline void Skeleton_Joint::clear_has_image_x() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void Skeleton_Joint::clear_image_x() {
  image_x_ = 0;
  clear_has_image_x();
}
inline float Skeleton_Joint::image_x() const {
  return image_x_;
}
inline void Skeleton_Joint::set_image_x(float value) {
  set_has_image_x();
  image_x_ = value;
}

// optional float image_y = 10;
inline bool Skeleton_Joint::has_image_y() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void Skeleton_Joint::set_has_image_y() {
  _has_bits_[0] |= 0x00000020u;
}
inline void Skeleton_Joint::clear_has_image_y() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void Skeleton_Joint::clear_image_y() {
  image_y_ = 0;
  clear_has_image_y();
}
inline float Skeleton_Joint::image_y() const {
  return image_y_;
}
inline void Skeleton_Joint::set_image_y(float value) {
  set_has_image_y();
  image_y_ = value;
}

// optional float qw = 5;
inline bool Skeleton_Joint::has_qw() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void Skeleton_Joint::set_has_qw() {
  _has_bits_[0] |= 0x00000040u;
}
inline void Skeleton_Joint::clear_has_qw() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void Skeleton_Joint::clear_qw() {
  qw_ = 0;
  clear_has_qw();
}
inline float Skeleton_Joint::qw() const {
  return qw_;
}
inline void Skeleton_Joint::set_qw(float value) {
  set_has_qw();
  qw_ = value;
}

// optional float qx = 6;
inline bool Skeleton_Joint::has_qx() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void Skeleton_Joint::set_has_qx() {
  _has_bits_[0] |= 0x00000080u;
}
inline void Skeleton_Joint::clear_has_qx() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void Skeleton_Joint::clear_qx() {
  qx_ = 0;
  clear_has_qx();
}
inline float Skeleton_Joint::qx() const {
  return qx_;
}
inline void Skeleton_Joint::set_qx(float value) {
  set_has_qx();
  qx_ = value;
}

// optional float qy = 7;
inline bool Skeleton_Joint::has_qy() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void Skeleton_Joint::set_has_qy() {
  _has_bits_[0] |= 0x00000100u;
}
inline void Skeleton_Joint::clear_has_qy() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void Skeleton_Joint::clear_qy() {
  qy_ = 0;
  clear_has_qy();
}
inline float Skeleton_Joint::qy() const {
  return qy_;
}
inline void Skeleton_Joint::set_qy(float value) {
  set_has_qy();
  qy_ = value;
}

// optional float qz = 8;
inline bool Skeleton_Joint::has_qz() const {
  return (_has_bits_[0] & 0x00000200u) != 0;
}
inline void Skeleton_Joint::set_has_qz() {
  _has_bits_[0] |= 0x00000200u;
}
inline void Skeleton_Joint::clear_has_qz() {
  _has_bits_[0] &= ~0x00000200u;
}
inline void Skeleton_Joint::clear_qz() {
  qz_ = 0;
  clear_has_qz();
}
inline float Skeleton_Joint::qz() const {
  return qz_;
}
inline void Skeleton_Joint::set_qz(float value) {
  set_has_qz();
  qz_ = value;
}

// -------------------------------------------------------------------

// Skeleton

// required string source_serial = 1;
inline bool Skeleton::has_source_serial() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Skeleton::set_has_source_serial() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Skeleton::clear_has_source_serial() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Skeleton::clear_source_serial() {
  if (source_serial_ != &::google::protobuf::internal::kEmptyString) {
    source_serial_->clear();
  }
  clear_has_source_serial();
}
inline const ::std::string& Skeleton::source_serial() const {
  return *source_serial_;
}
inline void Skeleton::set_source_serial(const ::std::string& value) {
  set_has_source_serial();
  if (source_serial_ == &::google::protobuf::internal::kEmptyString) {
    source_serial_ = new ::std::string;
  }
  source_serial_->assign(value);
}
inline void Skeleton::set_source_serial(const char* value) {
  set_has_source_serial();
  if (source_serial_ == &::google::protobuf::internal::kEmptyString) {
    source_serial_ = new ::std::string;
  }
  source_serial_->assign(value);
}
inline void Skeleton::set_source_serial(const char* value, size_t size) {
  set_has_source_serial();
  if (source_serial_ == &::google::protobuf::internal::kEmptyString) {
    source_serial_ = new ::std::string;
  }
  source_serial_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Skeleton::mutable_source_serial() {
  set_has_source_serial();
  if (source_serial_ == &::google::protobuf::internal::kEmptyString) {
    source_serial_ = new ::std::string;
  }
  return source_serial_;
}
inline ::std::string* Skeleton::release_source_serial() {
  clear_has_source_serial();
  if (source_serial_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = source_serial_;
    source_serial_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// required uint32 tick = 2;
inline bool Skeleton::has_tick() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Skeleton::set_has_tick() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Skeleton::clear_has_tick() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Skeleton::clear_tick() {
  tick_ = 0u;
  clear_has_tick();
}
inline ::google::protobuf::uint32 Skeleton::tick() const {
  return tick_;
}
inline void Skeleton::set_tick(::google::protobuf::uint32 value) {
  set_has_tick();
  tick_ = value;
}

// required uint32 skeleton_id = 3;
inline bool Skeleton::has_skeleton_id() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Skeleton::set_has_skeleton_id() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Skeleton::clear_has_skeleton_id() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Skeleton::clear_skeleton_id() {
  skeleton_id_ = 0u;
  clear_has_skeleton_id();
}
inline ::google::protobuf::uint32 Skeleton::skeleton_id() const {
  return skeleton_id_;
}
inline void Skeleton::set_skeleton_id(::google::protobuf::uint32 value) {
  set_has_skeleton_id();
  skeleton_id_ = value;
}

// repeated .RemoteKinect.Skeleton.Joint joints = 4;
inline int Skeleton::joints_size() const {
  return joints_.size();
}
inline void Skeleton::clear_joints() {
  joints_.Clear();
}
inline const ::RemoteKinect::Skeleton_Joint& Skeleton::joints(int index) const {
  return joints_.Get(index);
}
inline ::RemoteKinect::Skeleton_Joint* Skeleton::mutable_joints(int index) {
  return joints_.Mutable(index);
}
inline ::RemoteKinect::Skeleton_Joint* Skeleton::add_joints() {
  return joints_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::RemoteKinect::Skeleton_Joint >&
Skeleton::joints() const {
  return joints_;
}
inline ::google::protobuf::RepeatedPtrField< ::RemoteKinect::Skeleton_Joint >*
Skeleton::mutable_joints() {
  return &joints_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace RemoteKinect

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::RemoteKinect::Skeleton_Joint_Type>() {
  return ::RemoteKinect::Skeleton_Joint_Type_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_protocol_2fskeleton_2eproto__INCLUDED
