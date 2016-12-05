# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: stixels.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import ground_top_and_bottom_pb2 as ground__top__and__bottom__pb2
import plane3d_pb2 as plane3d__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='stixels.proto',
  package='doppia_protobuf',
  syntax='proto2',
  serialized_pb=_b('\n\rstixels.proto\x12\x0f\x64oppia_protobuf\x1a\x1bground_top_and_bottom.proto\x1a\rplane3d.proto\"\xa6\x02\n\x06Stixel\x12\r\n\x05width\x18\x01 \x02(\r\x12\t\n\x01x\x18\x02 \x02(\r\x12\x10\n\x08\x62ottom_y\x18\x03 \x02(\r\x12\r\n\x05top_y\x18\x04 \x02(\r\x12\x11\n\tdisparity\x18\x05 \x02(\r\x12*\n\x04type\x18\x06 \x02(\x0e\x32\x1c.doppia_protobuf.Stixel.Type\x12\x1b\n\x10\x62\x61\x63kward_delta_x\x18\x07 \x01(\x05:\x01\x30\x12\x1c\n\rvalid_delta_x\x18\x08 \x01(\x08:\x05\x66\x61lse\x12\x19\n\x0e\x62\x61\x63kward_width\x18\t \x01(\x05:\x01\x31\"L\n\x04Type\x12\x0b\n\x07Unknown\x10\x00\x12\x0c\n\x08Occluded\x10\x01\x12\x07\n\x03\x43\x61r\x10\x02\x12\x0e\n\nPedestrian\x10\x03\x12\x10\n\x0cStaticObject\x10\x04\"\xbb\x01\n\x07Stixels\x12\x12\n\nimage_name\x18\x01 \x01(\t\x12(\n\x07stixels\x18\x02 \x03(\x0b\x32\x17.doppia_protobuf.Stixel\x12\x42\n\x15ground_top_and_bottom\x18\x03 \x01(\x0b\x32#.doppia_protobuf.GroundTopAndBottom\x12.\n\x0cground_plane\x18\x04 \x01(\x0b\x32\x18.doppia_protobuf.Plane3d')
  ,
  dependencies=[ground__top__and__bottom__pb2.DESCRIPTOR,plane3d__pb2.DESCRIPTOR,])
_sym_db.RegisterFileDescriptor(DESCRIPTOR)



_STIXEL_TYPE = _descriptor.EnumDescriptor(
  name='Type',
  full_name='doppia_protobuf.Stixel.Type',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='Unknown', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='Occluded', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='Car', index=2, number=2,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='Pedestrian', index=3, number=3,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='StaticObject', index=4, number=4,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=297,
  serialized_end=373,
)
_sym_db.RegisterEnumDescriptor(_STIXEL_TYPE)


_STIXEL = _descriptor.Descriptor(
  name='Stixel',
  full_name='doppia_protobuf.Stixel',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='width', full_name='doppia_protobuf.Stixel.width', index=0,
      number=1, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='x', full_name='doppia_protobuf.Stixel.x', index=1,
      number=2, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='bottom_y', full_name='doppia_protobuf.Stixel.bottom_y', index=2,
      number=3, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='top_y', full_name='doppia_protobuf.Stixel.top_y', index=3,
      number=4, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='disparity', full_name='doppia_protobuf.Stixel.disparity', index=4,
      number=5, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='type', full_name='doppia_protobuf.Stixel.type', index=5,
      number=6, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='backward_delta_x', full_name='doppia_protobuf.Stixel.backward_delta_x', index=6,
      number=7, type=5, cpp_type=1, label=1,
      has_default_value=True, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='valid_delta_x', full_name='doppia_protobuf.Stixel.valid_delta_x', index=7,
      number=8, type=8, cpp_type=7, label=1,
      has_default_value=True, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='backward_width', full_name='doppia_protobuf.Stixel.backward_width', index=8,
      number=9, type=5, cpp_type=1, label=1,
      has_default_value=True, default_value=1,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _STIXEL_TYPE,
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=79,
  serialized_end=373,
)


_STIXELS = _descriptor.Descriptor(
  name='Stixels',
  full_name='doppia_protobuf.Stixels',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='image_name', full_name='doppia_protobuf.Stixels.image_name', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='stixels', full_name='doppia_protobuf.Stixels.stixels', index=1,
      number=2, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='ground_top_and_bottom', full_name='doppia_protobuf.Stixels.ground_top_and_bottom', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='ground_plane', full_name='doppia_protobuf.Stixels.ground_plane', index=3,
      number=4, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=376,
  serialized_end=563,
)

_STIXEL.fields_by_name['type'].enum_type = _STIXEL_TYPE
_STIXEL_TYPE.containing_type = _STIXEL
_STIXELS.fields_by_name['stixels'].message_type = _STIXEL
_STIXELS.fields_by_name['ground_top_and_bottom'].message_type = ground__top__and__bottom__pb2._GROUNDTOPANDBOTTOM
_STIXELS.fields_by_name['ground_plane'].message_type = plane3d__pb2._PLANE3D
DESCRIPTOR.message_types_by_name['Stixel'] = _STIXEL
DESCRIPTOR.message_types_by_name['Stixels'] = _STIXELS

Stixel = _reflection.GeneratedProtocolMessageType('Stixel', (_message.Message,), dict(
  DESCRIPTOR = _STIXEL,
  __module__ = 'stixels_pb2'
  # @@protoc_insertion_point(class_scope:doppia_protobuf.Stixel)
  ))
_sym_db.RegisterMessage(Stixel)

Stixels = _reflection.GeneratedProtocolMessageType('Stixels', (_message.Message,), dict(
  DESCRIPTOR = _STIXELS,
  __module__ = 'stixels_pb2'
  # @@protoc_insertion_point(class_scope:doppia_protobuf.Stixels)
  ))
_sym_db.RegisterMessage(Stixels)


# @@protoc_insertion_point(module_scope)
