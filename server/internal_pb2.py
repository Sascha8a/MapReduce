# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: internal.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf.internal import enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='internal.proto',
  package='mapreduce',
  syntax='proto3',
  serialized_pb=_b('\n\x0einternal.proto\x12\tmapreduce\"S\n\x03Job\x12\x0e\n\x06job_id\x18\x01 \x01(\t\x12\x0c\n\x04\x63ode\x18\x02 \x01(\t\x12\x1f\n\x03\x65xt\x18\x03 \x01(\x0e\x32\x12.mapreduce.CodeExt\x12\r\n\x05\x63hunk\x18\x04 \x03(\t\"\x1c\n\nJobRequest\x12\x0e\n\x06job_id\x18\x01 \x01(\t\"\x07\n\x05\x45mpty*\x1a\n\x07\x43odeExt\x12\x06\n\x02py\x10\x00\x12\x07\n\x03\x62in\x10\x01\x32\x08\n\x06Master2e\n\x04Node\x12,\n\x08StartJob\x12\x0e.mapreduce.Job\x1a\x10.mapreduce.Empty\x12/\n\x06GetJob\x12\x15.mapreduce.JobRequest\x1a\x0e.mapreduce.Job2\x08\n\x06Workerb\x06proto3')
)

_CODEEXT = _descriptor.EnumDescriptor(
  name='CodeExt',
  full_name='mapreduce.CodeExt',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='py', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='bin', index=1, number=1,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=153,
  serialized_end=179,
)
_sym_db.RegisterEnumDescriptor(_CODEEXT)

CodeExt = enum_type_wrapper.EnumTypeWrapper(_CODEEXT)
py = 0
bin = 1



_JOB = _descriptor.Descriptor(
  name='Job',
  full_name='mapreduce.Job',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='job_id', full_name='mapreduce.Job.job_id', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='code', full_name='mapreduce.Job.code', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='ext', full_name='mapreduce.Job.ext', index=2,
      number=3, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='chunk', full_name='mapreduce.Job.chunk', index=3,
      number=4, type=9, cpp_type=9, label=3,
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
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=29,
  serialized_end=112,
)


_JOBREQUEST = _descriptor.Descriptor(
  name='JobRequest',
  full_name='mapreduce.JobRequest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='job_id', full_name='mapreduce.JobRequest.job_id', index=0,
      number=1, type=9, cpp_type=9, label=1,
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
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=114,
  serialized_end=142,
)


_EMPTY = _descriptor.Descriptor(
  name='Empty',
  full_name='mapreduce.Empty',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=144,
  serialized_end=151,
)

_JOB.fields_by_name['ext'].enum_type = _CODEEXT
DESCRIPTOR.message_types_by_name['Job'] = _JOB
DESCRIPTOR.message_types_by_name['JobRequest'] = _JOBREQUEST
DESCRIPTOR.message_types_by_name['Empty'] = _EMPTY
DESCRIPTOR.enum_types_by_name['CodeExt'] = _CODEEXT
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

Job = _reflection.GeneratedProtocolMessageType('Job', (_message.Message,), dict(
  DESCRIPTOR = _JOB,
  __module__ = 'internal_pb2'
  # @@protoc_insertion_point(class_scope:mapreduce.Job)
  ))
_sym_db.RegisterMessage(Job)

JobRequest = _reflection.GeneratedProtocolMessageType('JobRequest', (_message.Message,), dict(
  DESCRIPTOR = _JOBREQUEST,
  __module__ = 'internal_pb2'
  # @@protoc_insertion_point(class_scope:mapreduce.JobRequest)
  ))
_sym_db.RegisterMessage(JobRequest)

Empty = _reflection.GeneratedProtocolMessageType('Empty', (_message.Message,), dict(
  DESCRIPTOR = _EMPTY,
  __module__ = 'internal_pb2'
  # @@protoc_insertion_point(class_scope:mapreduce.Empty)
  ))
_sym_db.RegisterMessage(Empty)



_MASTER = _descriptor.ServiceDescriptor(
  name='Master',
  full_name='mapreduce.Master',
  file=DESCRIPTOR,
  index=0,
  options=None,
  serialized_start=181,
  serialized_end=189,
  methods=[
])
_sym_db.RegisterServiceDescriptor(_MASTER)

DESCRIPTOR.services_by_name['Master'] = _MASTER


_NODE = _descriptor.ServiceDescriptor(
  name='Node',
  full_name='mapreduce.Node',
  file=DESCRIPTOR,
  index=1,
  options=None,
  serialized_start=191,
  serialized_end=292,
  methods=[
  _descriptor.MethodDescriptor(
    name='StartJob',
    full_name='mapreduce.Node.StartJob',
    index=0,
    containing_service=None,
    input_type=_JOB,
    output_type=_EMPTY,
    options=None,
  ),
  _descriptor.MethodDescriptor(
    name='GetJob',
    full_name='mapreduce.Node.GetJob',
    index=1,
    containing_service=None,
    input_type=_JOBREQUEST,
    output_type=_JOB,
    options=None,
  ),
])
_sym_db.RegisterServiceDescriptor(_NODE)

DESCRIPTOR.services_by_name['Node'] = _NODE


_WORKER = _descriptor.ServiceDescriptor(
  name='Worker',
  full_name='mapreduce.Worker',
  file=DESCRIPTOR,
  index=2,
  options=None,
  serialized_start=294,
  serialized_end=302,
  methods=[
])
_sym_db.RegisterServiceDescriptor(_WORKER)

DESCRIPTOR.services_by_name['Worker'] = _WORKER

# @@protoc_insertion_point(module_scope)