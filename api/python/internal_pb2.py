# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: internal.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf.internal import enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='internal.proto',
  package='mapreduce',
  syntax='proto3',
  serialized_options=None,
  serialized_pb=_b('\n\x0einternal.proto\x12\tmapreduce\"*\n\x0cKeyValuePair\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\x05\"C\n\tMappedJob\x12\x0e\n\x06job_id\x18\x01 \x01(\t\x12&\n\x05pairs\x18\x04 \x03(\x0b\x32\x17.mapreduce.KeyValuePair\"\x81\x01\n\x03Job\x12\x0e\n\x06job_id\x18\x01 \x01(\t\x12\x0c\n\x04\x63ode\x18\x02 \x01(\t\x12\x1f\n\x03\x65xt\x18\x03 \x01(\x0e\x32\x12.mapreduce.CodeExt\x12\x0e\n\x06\x63hunks\x18\x04 \x03(\t\x12+\n\nmapresults\x18\x05 \x03(\x0b\x32\x17.mapreduce.KeyValuePair\"\x1c\n\nJobRequest\x12\x0e\n\x06job_id\x18\x01 \x01(\t\"\x07\n\x05\x45mpty*\x1a\n\x07\x43odeExt\x12\x06\n\x02py\x10\x00\x12\x07\n\x03\x62in\x10\x01\x32\x08\n\x06Master2\x9a\x01\n\x04Node\x12,\n\x08JobStart\x12\x0e.mapreduce.Job\x1a\x10.mapreduce.Empty\x12/\n\x06JobGet\x12\x15.mapreduce.JobRequest\x1a\x0e.mapreduce.Job\x12\x33\n\tJobMapped\x12\x14.mapreduce.MappedJob\x1a\x10.mapreduce.Empty2\x08\n\x06Workerb\x06proto3')
)

_CODEEXT = _descriptor.EnumDescriptor(
  name='CodeExt',
  full_name='mapreduce.CodeExt',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='py', index=0, number=0,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='bin', index=1, number=1,
      serialized_options=None,
      type=None),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=313,
  serialized_end=339,
)
_sym_db.RegisterEnumDescriptor(_CODEEXT)

CodeExt = enum_type_wrapper.EnumTypeWrapper(_CODEEXT)
py = 0
bin = 1



_KEYVALUEPAIR = _descriptor.Descriptor(
  name='KeyValuePair',
  full_name='mapreduce.KeyValuePair',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='key', full_name='mapreduce.KeyValuePair.key', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='value', full_name='mapreduce.KeyValuePair.value', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=29,
  serialized_end=71,
)


_MAPPEDJOB = _descriptor.Descriptor(
  name='MappedJob',
  full_name='mapreduce.MappedJob',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='job_id', full_name='mapreduce.MappedJob.job_id', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='pairs', full_name='mapreduce.MappedJob.pairs', index=1,
      number=4, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=73,
  serialized_end=140,
)


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
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='code', full_name='mapreduce.Job.code', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='ext', full_name='mapreduce.Job.ext', index=2,
      number=3, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='chunks', full_name='mapreduce.Job.chunks', index=3,
      number=4, type=9, cpp_type=9, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='mapresults', full_name='mapreduce.Job.mapresults', index=4,
      number=5, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=143,
  serialized_end=272,
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
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=274,
  serialized_end=302,
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
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=304,
  serialized_end=311,
)

_MAPPEDJOB.fields_by_name['pairs'].message_type = _KEYVALUEPAIR
_JOB.fields_by_name['ext'].enum_type = _CODEEXT
_JOB.fields_by_name['mapresults'].message_type = _KEYVALUEPAIR
DESCRIPTOR.message_types_by_name['KeyValuePair'] = _KEYVALUEPAIR
DESCRIPTOR.message_types_by_name['MappedJob'] = _MAPPEDJOB
DESCRIPTOR.message_types_by_name['Job'] = _JOB
DESCRIPTOR.message_types_by_name['JobRequest'] = _JOBREQUEST
DESCRIPTOR.message_types_by_name['Empty'] = _EMPTY
DESCRIPTOR.enum_types_by_name['CodeExt'] = _CODEEXT
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

KeyValuePair = _reflection.GeneratedProtocolMessageType('KeyValuePair', (_message.Message,), dict(
  DESCRIPTOR = _KEYVALUEPAIR,
  __module__ = 'internal_pb2'
  # @@protoc_insertion_point(class_scope:mapreduce.KeyValuePair)
  ))
_sym_db.RegisterMessage(KeyValuePair)

MappedJob = _reflection.GeneratedProtocolMessageType('MappedJob', (_message.Message,), dict(
  DESCRIPTOR = _MAPPEDJOB,
  __module__ = 'internal_pb2'
  # @@protoc_insertion_point(class_scope:mapreduce.MappedJob)
  ))
_sym_db.RegisterMessage(MappedJob)

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
  serialized_options=None,
  serialized_start=341,
  serialized_end=349,
  methods=[
])
_sym_db.RegisterServiceDescriptor(_MASTER)

DESCRIPTOR.services_by_name['Master'] = _MASTER


_NODE = _descriptor.ServiceDescriptor(
  name='Node',
  full_name='mapreduce.Node',
  file=DESCRIPTOR,
  index=1,
  serialized_options=None,
  serialized_start=352,
  serialized_end=506,
  methods=[
  _descriptor.MethodDescriptor(
    name='JobStart',
    full_name='mapreduce.Node.JobStart',
    index=0,
    containing_service=None,
    input_type=_JOB,
    output_type=_EMPTY,
    serialized_options=None,
  ),
  _descriptor.MethodDescriptor(
    name='JobGet',
    full_name='mapreduce.Node.JobGet',
    index=1,
    containing_service=None,
    input_type=_JOBREQUEST,
    output_type=_JOB,
    serialized_options=None,
  ),
  _descriptor.MethodDescriptor(
    name='JobMapped',
    full_name='mapreduce.Node.JobMapped',
    index=2,
    containing_service=None,
    input_type=_MAPPEDJOB,
    output_type=_EMPTY,
    serialized_options=None,
  ),
])
_sym_db.RegisterServiceDescriptor(_NODE)

DESCRIPTOR.services_by_name['Node'] = _NODE


_WORKER = _descriptor.ServiceDescriptor(
  name='Worker',
  full_name='mapreduce.Worker',
  file=DESCRIPTOR,
  index=2,
  serialized_options=None,
  serialized_start=508,
  serialized_end=516,
  methods=[
])
_sym_db.RegisterServiceDescriptor(_WORKER)

DESCRIPTOR.services_by_name['Worker'] = _WORKER

# @@protoc_insertion_point(module_scope)
