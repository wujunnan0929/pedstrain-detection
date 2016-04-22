// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ground_top_and_bottom.proto

#ifndef PROTOBUF_ground_5ftop_5fand_5fbottom_2eproto__INCLUDED
#define PROTOBUF_ground_5ftop_5fand_5fbottom_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace doppia_protobuf {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ground_5ftop_5fand_5fbottom_2eproto();
void protobuf_AssignDesc_ground_5ftop_5fand_5fbottom_2eproto();
void protobuf_ShutdownFile_ground_5ftop_5fand_5fbottom_2eproto();

class TopAndBottom;
class GroundTopAndBottom;

// ===================================================================

class TopAndBottom : public ::google::protobuf::Message {
 public:
  TopAndBottom();
  virtual ~TopAndBottom();

  TopAndBottom(const TopAndBottom& from);

  inline TopAndBottom& operator=(const TopAndBottom& from) {
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
  static const TopAndBottom& default_instance();

  void Swap(TopAndBottom* other);

  // implements Message ----------------------------------------------

  TopAndBottom* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TopAndBottom& from);
  void MergeFrom(const TopAndBottom& from);
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

  // accessors -------------------------------------------------------

  // required uint32 top_y = 1;
  inline bool has_top_y() const;
  inline void clear_top_y();
  static const int kTopYFieldNumber = 1;
  inline ::google::protobuf::uint32 top_y() const;
  inline void set_top_y(::google::protobuf::uint32 value);

  // required uint32 bottom_y = 2;
  inline bool has_bottom_y() const;
  inline void clear_bottom_y();
  static const int kBottomYFieldNumber = 2;
  inline ::google::protobuf::uint32 bottom_y() const;
  inline void set_bottom_y(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:doppia_protobuf.TopAndBottom)
 private:
  inline void set_has_top_y();
  inline void clear_has_top_y();
  inline void set_has_bottom_y();
  inline void clear_has_bottom_y();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 top_y_;
  ::google::protobuf::uint32 bottom_y_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_ground_5ftop_5fand_5fbottom_2eproto();
  friend void protobuf_AssignDesc_ground_5ftop_5fand_5fbottom_2eproto();
  friend void protobuf_ShutdownFile_ground_5ftop_5fand_5fbottom_2eproto();

  void InitAsDefaultInstance();
  static TopAndBottom* default_instance_;
};
// -------------------------------------------------------------------

class GroundTopAndBottom : public ::google::protobuf::Message {
 public:
  GroundTopAndBottom();
  virtual ~GroundTopAndBottom();

  GroundTopAndBottom(const GroundTopAndBottom& from);

  inline GroundTopAndBottom& operator=(const GroundTopAndBottom& from) {
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
  static const GroundTopAndBottom& default_instance();

  void Swap(GroundTopAndBottom* other);

  // implements Message ----------------------------------------------

  GroundTopAndBottom* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GroundTopAndBottom& from);
  void MergeFrom(const GroundTopAndBottom& from);
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

  // accessors -------------------------------------------------------

  // repeated .doppia_protobuf.TopAndBottom top_and_bottom = 1;
  inline int top_and_bottom_size() const;
  inline void clear_top_and_bottom();
  static const int kTopAndBottomFieldNumber = 1;
  inline const ::doppia_protobuf::TopAndBottom& top_and_bottom(int index) const;
  inline ::doppia_protobuf::TopAndBottom* mutable_top_and_bottom(int index);
  inline ::doppia_protobuf::TopAndBottom* add_top_and_bottom();
  inline const ::google::protobuf::RepeatedPtrField< ::doppia_protobuf::TopAndBottom >&
      top_and_bottom() const;
  inline ::google::protobuf::RepeatedPtrField< ::doppia_protobuf::TopAndBottom >*
      mutable_top_and_bottom();

  // @@protoc_insertion_point(class_scope:doppia_protobuf.GroundTopAndBottom)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::doppia_protobuf::TopAndBottom > top_and_bottom_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_ground_5ftop_5fand_5fbottom_2eproto();
  friend void protobuf_AssignDesc_ground_5ftop_5fand_5fbottom_2eproto();
  friend void protobuf_ShutdownFile_ground_5ftop_5fand_5fbottom_2eproto();

  void InitAsDefaultInstance();
  static GroundTopAndBottom* default_instance_;
};
// ===================================================================


// ===================================================================

// TopAndBottom

// required uint32 top_y = 1;
inline bool TopAndBottom::has_top_y() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TopAndBottom::set_has_top_y() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TopAndBottom::clear_has_top_y() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TopAndBottom::clear_top_y() {
  top_y_ = 0u;
  clear_has_top_y();
}
inline ::google::protobuf::uint32 TopAndBottom::top_y() const {
  return top_y_;
}
inline void TopAndBottom::set_top_y(::google::protobuf::uint32 value) {
  set_has_top_y();
  top_y_ = value;
}

// required uint32 bottom_y = 2;
inline bool TopAndBottom::has_bottom_y() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TopAndBottom::set_has_bottom_y() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TopAndBottom::clear_has_bottom_y() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TopAndBottom::clear_bottom_y() {
  bottom_y_ = 0u;
  clear_has_bottom_y();
}
inline ::google::protobuf::uint32 TopAndBottom::bottom_y() const {
  return bottom_y_;
}
inline void TopAndBottom::set_bottom_y(::google::protobuf::uint32 value) {
  set_has_bottom_y();
  bottom_y_ = value;
}

// -------------------------------------------------------------------

// GroundTopAndBottom

// repeated .doppia_protobuf.TopAndBottom top_and_bottom = 1;
inline int GroundTopAndBottom::top_and_bottom_size() const {
  return top_and_bottom_.size();
}
inline void GroundTopAndBottom::clear_top_and_bottom() {
  top_and_bottom_.Clear();
}
inline const ::doppia_protobuf::TopAndBottom& GroundTopAndBottom::top_and_bottom(int index) const {
  return top_and_bottom_.Get(index);
}
inline ::doppia_protobuf::TopAndBottom* GroundTopAndBottom::mutable_top_and_bottom(int index) {
  return top_and_bottom_.Mutable(index);
}
inline ::doppia_protobuf::TopAndBottom* GroundTopAndBottom::add_top_and_bottom() {
  return top_and_bottom_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::doppia_protobuf::TopAndBottom >&
GroundTopAndBottom::top_and_bottom() const {
  return top_and_bottom_;
}
inline ::google::protobuf::RepeatedPtrField< ::doppia_protobuf::TopAndBottom >*
GroundTopAndBottom::mutable_top_and_bottom() {
  return &top_and_bottom_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace doppia_protobuf

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ground_5ftop_5fand_5fbottom_2eproto__INCLUDED
