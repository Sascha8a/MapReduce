# Generated by the gRPC Python protocol compiler plugin. DO NOT EDIT!
import grpc

import internal_pb2 as internal__pb2


class MasterStub(object):
  # missing associated documentation comment in .proto file
  pass

  def __init__(self, channel):
    """Constructor.

    Args:
      channel: A grpc.Channel.
    """
    self.RegisterNode = channel.unary_unary(
        '/mapreduce.Master/RegisterNode',
        request_serializer=internal__pb2.NewNode.SerializeToString,
        response_deserializer=internal__pb2.Empty.FromString,
        )
    self.JobStart = channel.unary_unary(
        '/mapreduce.Master/JobStart',
        request_serializer=internal__pb2.NewJob.SerializeToString,
        response_deserializer=internal__pb2.Empty.FromString,
        )


class MasterServicer(object):
  # missing associated documentation comment in .proto file
  pass

  def RegisterNode(self, request, context):
    # missing associated documentation comment in .proto file
    pass
    context.set_code(grpc.StatusCode.UNIMPLEMENTED)
    context.set_details('Method not implemented!')
    raise NotImplementedError('Method not implemented!')

  def JobStart(self, request, context):
    # missing associated documentation comment in .proto file
    pass
    context.set_code(grpc.StatusCode.UNIMPLEMENTED)
    context.set_details('Method not implemented!')
    raise NotImplementedError('Method not implemented!')


def add_MasterServicer_to_server(servicer, server):
  rpc_method_handlers = {
      'RegisterNode': grpc.unary_unary_rpc_method_handler(
          servicer.RegisterNode,
          request_deserializer=internal__pb2.NewNode.FromString,
          response_serializer=internal__pb2.Empty.SerializeToString,
      ),
      'JobStart': grpc.unary_unary_rpc_method_handler(
          servicer.JobStart,
          request_deserializer=internal__pb2.NewJob.FromString,
          response_serializer=internal__pb2.Empty.SerializeToString,
      ),
  }
  generic_handler = grpc.method_handlers_generic_handler(
      'mapreduce.Master', rpc_method_handlers)
  server.add_generic_rpc_handlers((generic_handler,))


class NodeStub(object):
  # missing associated documentation comment in .proto file
  pass

  def __init__(self, channel):
    """Constructor.

    Args:
      channel: A grpc.Channel.
    """
    self.StartTask = channel.unary_unary(
        '/mapreduce.Node/StartTask',
        request_serializer=internal__pb2.Task.SerializeToString,
        response_deserializer=internal__pb2.Empty.FromString,
        )
    self.JobStart = channel.unary_unary(
        '/mapreduce.Node/JobStart',
        request_serializer=internal__pb2.Job.SerializeToString,
        response_deserializer=internal__pb2.Empty.FromString,
        )
    self.JobGet = channel.unary_unary(
        '/mapreduce.Node/JobGet',
        request_serializer=internal__pb2.JobRequest.SerializeToString,
        response_deserializer=internal__pb2.Job.FromString,
        )
    self.JobMapped = channel.unary_unary(
        '/mapreduce.Node/JobMapped',
        request_serializer=internal__pb2.MappedJob.SerializeToString,
        response_deserializer=internal__pb2.Empty.FromString,
        )


class NodeServicer(object):
  # missing associated documentation comment in .proto file
  pass

  def StartTask(self, request, context):
    # missing associated documentation comment in .proto file
    pass
    context.set_code(grpc.StatusCode.UNIMPLEMENTED)
    context.set_details('Method not implemented!')
    raise NotImplementedError('Method not implemented!')

  def JobStart(self, request, context):
    # missing associated documentation comment in .proto file
    pass
    context.set_code(grpc.StatusCode.UNIMPLEMENTED)
    context.set_details('Method not implemented!')
    raise NotImplementedError('Method not implemented!')

  def JobGet(self, request, context):
    # missing associated documentation comment in .proto file
    pass
    context.set_code(grpc.StatusCode.UNIMPLEMENTED)
    context.set_details('Method not implemented!')
    raise NotImplementedError('Method not implemented!')

  def JobMapped(self, request, context):
    # missing associated documentation comment in .proto file
    pass
    context.set_code(grpc.StatusCode.UNIMPLEMENTED)
    context.set_details('Method not implemented!')
    raise NotImplementedError('Method not implemented!')


def add_NodeServicer_to_server(servicer, server):
  rpc_method_handlers = {
      'StartTask': grpc.unary_unary_rpc_method_handler(
          servicer.StartTask,
          request_deserializer=internal__pb2.Task.FromString,
          response_serializer=internal__pb2.Empty.SerializeToString,
      ),
      'JobStart': grpc.unary_unary_rpc_method_handler(
          servicer.JobStart,
          request_deserializer=internal__pb2.Job.FromString,
          response_serializer=internal__pb2.Empty.SerializeToString,
      ),
      'JobGet': grpc.unary_unary_rpc_method_handler(
          servicer.JobGet,
          request_deserializer=internal__pb2.JobRequest.FromString,
          response_serializer=internal__pb2.Job.SerializeToString,
      ),
      'JobMapped': grpc.unary_unary_rpc_method_handler(
          servicer.JobMapped,
          request_deserializer=internal__pb2.MappedJob.FromString,
          response_serializer=internal__pb2.Empty.SerializeToString,
      ),
  }
  generic_handler = grpc.method_handlers_generic_handler(
      'mapreduce.Node', rpc_method_handlers)
  server.add_generic_rpc_handlers((generic_handler,))


class WorkerStub(object):
  # missing associated documentation comment in .proto file
  pass

  def __init__(self, channel):
    """Constructor.

    Args:
      channel: A grpc.Channel.
    """


class WorkerServicer(object):
  # missing associated documentation comment in .proto file
  pass


def add_WorkerServicer_to_server(servicer, server):
  rpc_method_handlers = {
  }
  generic_handler = grpc.method_handlers_generic_handler(
      'mapreduce.Worker', rpc_method_handlers)
  server.add_generic_rpc_handlers((generic_handler,))
