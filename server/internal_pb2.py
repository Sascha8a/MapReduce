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
  serialized_pb=_b('\n\x0einternal.proto\x12\tmapreduce\"\x1a\n\x07NewNode\x12\x0f\n\x07\x63onnstr\x18\x01 \x01(\t\"V\n\x06MapJob\x12\x0e\n\x06job_id\x18\x01 \x01(\x03\x12\x0c\n\x04\x63ode\x18\x02 \x01(\t\x12\x1f\n\x03\x65xt\x18\x03 \x01(\x0e\x32\x12.mapreduce.CodeExt\x12\r\n\x05\x63hunk\x18\x04 \x01(\t\"f\n\tReduceJob\x12\x0e\n\x06job_id\x18\x01 \x01(\x03\x12\x0c\n\x04\x63ode\x18\x02 \x01(\t\x12\x1f\n\x03\x65xt\x18\x03 \x01(\x0e\x32\x12.mapreduce.CodeExt\x12\x0b\n\x03key\x18\x04 \x01(\t\x12\r\n\x05value\x18\x05 \x03(\x05\"*\n\x0cKeyValuePair\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\x05\"?\n\tMappedJob\x12\n\n\x02id\x18\x01 \x01(\x03\x12&\n\x05pairs\x18\x02 \x03(\x0b\x32\x17.mapreduce.KeyValuePair\"5\n\nReducedJob\x12\n\n\x02id\x18\x01 \x01(\x03\x12\x0b\n\x03key\x18\x02 \x01(\t\x12\x0e\n\x06result\x18\x03 \x01(\x03\"$\n\x06NewJob\x12\x0c\n\x04\x63ode\x18\x01 \x01(\t\x12\x0c\n\x04\x64\x61ta\x18\x02 \x01(\t\"<\n\x03Job\x12\n\n\x02id\x18\x01 \x01(\x03\x12\r\n\x05\x63hunk\x18\x02 \x01(\t\x12\x0b\n\x03key\x18\x03 \x01(\t\x12\r\n\x05value\x18\x04 \x03(\x05\"\x07\n\x05\x45mpty\"\x1f\n\x04Task\x12\n\n\x02id\x18\x01 \x01(\x03\x12\x0b\n\x03job\x18\x02 \x01(\x0c*\x1a\n\x07\x43odeExt\x12\x06\n\x02py\x10\x00\x12\x07\n\x03\x62in\x10\x01\x32m\n\x06Master\x12\x34\n\x0cRegisterNode\x12\x12.mapreduce.NewNode\x1a\x10.mapreduce.Empty\x12-\n\x08TaskDone\x12\x0f.mapreduce.Task\x1a\x10.mapreduce.Empty2\xce\x01\n\x04Node\x12.\n\tStartTask\x12\x0f.mapreduce.Task\x1a\x10.mapreduce.Empty\x12*\n\x06JobGet\x12\x10.mapreduce.Empty\x1a\x0e.mapreduce.Job\x12\x33\n\tJobMapped\x12\x14.mapreduce.MappedJob\x1a\x10.mapreduce.Empty\x12\x35\n\nJobReduced\x12\x15.mapreduce.ReducedJob\x1a\x10.mapreduce.Empty2\x08\n\x06Workerb\x06proto3')
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
  serialized_start=555,
  serialized_end=581,
)
_sym_db.RegisterEnumDescriptor(_CODEEXT)

CodeExt = enum_type_wrapper.EnumTypeWrapper(_CODEEXT)
py = 0
bin = 1



_NEWNODE = _descriptor.Descriptor(
  name='NewNode',
  full_name='mapreduce.NewNode',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='connstr', full_name='mapreduce.NewNode.connstr', index=0,
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
  serialized_start=29,
  serialized_end=55,
)


_MAPJOB = _descriptor.Descriptor(
  name='MapJob',
  full_name='mapreduce.MapJob',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='job_id', full_name='mapreduce.MapJob.job_id', index=0,
      number=1, type=3, cpp_type=2, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='code', full_name='mapreduce.MapJob.code', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='ext', full_name='mapreduce.MapJob.ext', index=2,
      number=3, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='chunk', full_name='mapreduce.MapJob.chunk', index=3,
      number=4, type=9, cpp_type=9, label=1,
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
  serialized_start=57,
  serialized_end=143,
)


_REDUCEJOB = _descriptor.Descriptor(
  name='ReduceJob',
  full_name='mapreduce.ReduceJob',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='job_id', full_name='mapreduce.ReduceJob.job_id', index=0,
      number=1, type=3, cpp_type=2, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='code', full_name='mapreduce.ReduceJob.code', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='ext', full_name='mapreduce.ReduceJob.ext', index=2,
      number=3, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='key', full_name='mapreduce.ReduceJob.key', index=3,
      number=4, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='value', full_name='mapreduce.ReduceJob.value', index=4,
      number=5, type=5, cpp_type=1, label=3,
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
  serialized_start=145,
  serialized_end=247,
)


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
  serialized_start=249,
  serialized_end=291,
)


_MAPPEDJOB = _descriptor.Descriptor(
  name='MappedJob',
  full_name='mapreduce.MappedJob',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='id', full_name='mapreduce.MappedJob.id', index=0,
      number=1, type=3, cpp_type=2, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='pairs', full_name='mapreduce.MappedJob.pairs', index=1,
      number=2, type=11, cpp_type=10, label=3,
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
  serialized_start=293,
  serialized_end=356,
)


_REDUCEDJOB = _descriptor.Descriptor(
  name='ReducedJob',
  full_name='mapreduce.ReducedJob',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='id', full_name='mapreduce.ReducedJob.id', index=0,
      number=1, type=3, cpp_type=2, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='key', full_name='mapreduce.ReducedJob.key', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='result', full_name='mapreduce.ReducedJob.result', index=2,
      number=3, type=3, cpp_type=2, label=1,
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
  serialized_start=358,
  serialized_end=411,
)


_NEWJOB = _descriptor.Descriptor(
  name='NewJob',
  full_name='mapreduce.NewJob',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='code', full_name='mapreduce.NewJob.code', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='data', full_name='mapreduce.NewJob.data', index=1,
      number=2, type=9, cpp_type=9, label=1,
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
  serialized_start=413,
  serialized_end=449,
)


_JOB = _descriptor.Descriptor(
  name='Job',
  full_name='mapreduce.Job',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='id', full_name='mapreduce.Job.id', index=0,
      number=1, type=3, cpp_type=2, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='chunk', full_name='mapreduce.Job.chunk', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='key', full_name='mapreduce.Job.key', index=2,
      number=3, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='value', full_name='mapreduce.Job.value', index=3,
      number=4, type=5, cpp_type=1, label=3,
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
  serialized_start=451,
  serialized_end=511,
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
  serialized_start=513,
  serialized_end=520,
)


_TASK = _descriptor.Descriptor(
  name='Task',
  full_name='mapreduce.Task',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='id', full_name='mapreduce.Task.id', index=0,
      number=1, type=3, cpp_type=2, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='job', full_name='mapreduce.Task.job', index=1,
      number=2, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=_b(""),
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
  serialized_start=522,
  serialized_end=553,
)

_MAPJOB.fields_by_name['ext'].enum_type = _CODEEXT
_REDUCEJOB.fields_by_name['ext'].enum_type = _CODEEXT
_MAPPEDJOB.fields_by_name['pairs'].message_type = _KEYVALUEPAIR
DESCRIPTOR.message_types_by_name['NewNode'] = _NEWNODE
DESCRIPTOR.message_types_by_name['MapJob'] = _MAPJOB
DESCRIPTOR.message_types_by_name['ReduceJob'] = _REDUCEJOB
DESCRIPTOR.message_types_by_name['KeyValuePair'] = _KEYVALUEPAIR
DESCRIPTOR.message_types_by_name['MappedJob'] = _MAPPEDJOB
DESCRIPTOR.message_types_by_name['ReducedJob'] = _REDUCEDJOB
DESCRIPTOR.message_types_by_name['NewJob'] = _NEWJOB
DESCRIPTOR.message_types_by_name['Job'] = _JOB
DESCRIPTOR.message_types_by_name['Empty'] = _EMPTY
DESCRIPTOR.message_types_by_name['Task'] = _TASK
DESCRIPTOR.enum_types_by_name['CodeExt'] = _CODEEXT
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

NewNode = _reflection.GeneratedProtocolMessageType('NewNode', (_message.Message,), dict(
  DESCRIPTOR = _NEWNODE,
  __module__ = 'internal_pb2'
  # @@protoc_insertion_point(class_scope:mapreduce.NewNode)
  ))
_sym_db.RegisterMessage(NewNode)

MapJob = _reflection.GeneratedProtocolMessageType('MapJob', (_message.Message,), dict(
  DESCRIPTOR = _MAPJOB,
  __module__ = 'internal_pb2'
  # @@protoc_insertion_point(class_scope:mapreduce.MapJob)
  ))
_sym_db.RegisterMessage(MapJob)

ReduceJob = _reflection.GeneratedProtocolMessageType('ReduceJob', (_message.Message,), dict(
  DESCRIPTOR = _REDUCEJOB,
  __module__ = 'internal_pb2'
  # @@protoc_insertion_point(class_scope:mapreduce.ReduceJob)
  ))
_sym_db.RegisterMessage(ReduceJob)

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

ReducedJob = _reflection.GeneratedProtocolMessageType('ReducedJob', (_message.Message,), dict(
  DESCRIPTOR = _REDUCEDJOB,
  __module__ = 'internal_pb2'
  # @@protoc_insertion_point(class_scope:mapreduce.ReducedJob)
  ))
_sym_db.RegisterMessage(ReducedJob)

NewJob = _reflection.GeneratedProtocolMessageType('NewJob', (_message.Message,), dict(
  DESCRIPTOR = _NEWJOB,
  __module__ = 'internal_pb2'
  # @@protoc_insertion_point(class_scope:mapreduce.NewJob)
  ))
_sym_db.RegisterMessage(NewJob)

Job = _reflection.GeneratedProtocolMessageType('Job', (_message.Message,), dict(
  DESCRIPTOR = _JOB,
  __module__ = 'internal_pb2'
  # @@protoc_insertion_point(class_scope:mapreduce.Job)
  ))
_sym_db.RegisterMessage(Job)

Empty = _reflection.GeneratedProtocolMessageType('Empty', (_message.Message,), dict(
  DESCRIPTOR = _EMPTY,
  __module__ = 'internal_pb2'
  # @@protoc_insertion_point(class_scope:mapreduce.Empty)
  ))
_sym_db.RegisterMessage(Empty)

Task = _reflection.GeneratedProtocolMessageType('Task', (_message.Message,), dict(
  DESCRIPTOR = _TASK,
  __module__ = 'internal_pb2'
  # @@protoc_insertion_point(class_scope:mapreduce.Task)
  ))
_sym_db.RegisterMessage(Task)



_MASTER = _descriptor.ServiceDescriptor(
  name='Master',
  full_name='mapreduce.Master',
  file=DESCRIPTOR,
  index=0,
  serialized_options=None,
  serialized_start=583,
  serialized_end=692,
  methods=[
  _descriptor.MethodDescriptor(
    name='RegisterNode',
    full_name='mapreduce.Master.RegisterNode',
    index=0,
    containing_service=None,
    input_type=_NEWNODE,
    output_type=_EMPTY,
    serialized_options=None,
  ),
  _descriptor.MethodDescriptor(
    name='TaskDone',
    full_name='mapreduce.Master.TaskDone',
    index=1,
    containing_service=None,
    input_type=_TASK,
    output_type=_EMPTY,
    serialized_options=None,
  ),
])
_sym_db.RegisterServiceDescriptor(_MASTER)

DESCRIPTOR.services_by_name['Master'] = _MASTER


_NODE = _descriptor.ServiceDescriptor(
  name='Node',
  full_name='mapreduce.Node',
  file=DESCRIPTOR,
  index=1,
  serialized_options=None,
  serialized_start=695,
  serialized_end=901,
  methods=[
  _descriptor.MethodDescriptor(
    name='StartTask',
    full_name='mapreduce.Node.StartTask',
    index=0,
    containing_service=None,
    input_type=_TASK,
    output_type=_EMPTY,
    serialized_options=None,
  ),
  _descriptor.MethodDescriptor(
    name='JobGet',
    full_name='mapreduce.Node.JobGet',
    index=1,
    containing_service=None,
    input_type=_EMPTY,
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
  _descriptor.MethodDescriptor(
    name='JobReduced',
    full_name='mapreduce.Node.JobReduced',
    index=3,
    containing_service=None,
    input_type=_REDUCEDJOB,
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
  serialized_start=903,
  serialized_end=911,
  methods=[
])
_sym_db.RegisterServiceDescriptor(_WORKER)

DESCRIPTOR.services_by_name['Worker'] = _WORKER

# @@protoc_insertion_point(module_scope)
