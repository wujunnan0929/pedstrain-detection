# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: DataSequenceHeader.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='DataSequenceHeader.proto',
  package='doppia_protobuf',
  syntax='proto2',
  serialized_pb=_b('\n\x18\x44\x61taSequenceHeader.proto\x12\x0f\x64oppia_protobuf\"4\n\x15\x44\x61taSequenceAttribute\x12\x0c\n\x04name\x18\x01 \x02(\t\x12\r\n\x05value\x18\x02 \x02(\t\"P\n\x12\x44\x61taSequenceHeader\x12:\n\nattributes\x18\x03 \x03(\x0b\x32&.doppia_protobuf.DataSequenceAttribute')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_DATASEQUENCEATTRIBUTE = _descriptor.Descriptor(
  name='DataSequenceAttribute',
  full_name='doppia_protobuf.DataSequenceAttribute',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='name', full_name='doppia_protobuf.DataSequenceAttribute.name', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='value', full_name='doppia_protobuf.DataSequenceAttribute.value', index=1,
      number=2, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
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
  serialized_start=45,
  serialized_end=97,
)


_DATASEQUENCEHEADER = _descriptor.Descriptor(
  name='DataSequenceHeader',
  full_name='doppia_protobuf.DataSequenceHeader',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='attributes', full_name='doppia_protobuf.DataSequenceHeader.attributes', index=0,
      number=3, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
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
  serialized_start=99,
  serialized_end=179,
)

_DATASEQUENCEHEADER.fields_by_name['attributes'].message_type = _DATASEQUENCEATTRIBUTE
DESCRIPTOR.message_types_by_name['DataSequenceAttribute'] = _DATASEQUENCEATTRIBUTE
DESCRIPTOR.message_types_by_name['DataSequenceHeader'] = _DATASEQUENCEHEADER

DataSequenceAttribute = _reflection.GeneratedProtocolMessageType('DataSequenceAttribute', (_message.Message,), dict(
  DESCRIPTOR = _DATASEQUENCEATTRIBUTE,
  __module__ = 'DataSequenceHeader_pb2'
  # @@protoc_insertion_point(class_scope:doppia_protobuf.DataSequenceAttribute)
  ))
_sym_db.RegisterMessage(DataSequenceAttribute)

DataSequenceHeader = _reflection.GeneratedProtocolMessageType('DataSequenceHeader', (_message.Message,), dict(
  DESCRIPTOR = _DATASEQUENCEHEADER,
  __module__ = 'DataSequenceHeader_pb2'
  # @@protoc_insertion_point(class_scope:doppia_protobuf.DataSequenceHeader)
  ))
_sym_db.RegisterMessage(DataSequenceHeader)


# @@protoc_insertion_point(module_scope)
