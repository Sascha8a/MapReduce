import grpc
import internal_pb2
import internal_pb2_grpc
import json

class Worker:
  def return_mapped(self, result):
    with grpc.insecure_channel('localhost:50051') as channel:

      results_message = internal_pb2.MapResults(job_id="aaa")
      for key in result:
        results_message.pairs[key] = result[key]

      stub = internal_pb2_grpc.NodeStub(channel)
      stub.MappedJob(results_message)

  def __init__(self, map_func, reduce_func):
    with grpc.insecure_channel('localhost:50051') as channel:
      stub = internal_pb2_grpc.NodeStub(channel)
      job = stub.GetJob(internal_pb2.JobRequest(job_id="aaa"))
      
      if (job.chunks):
        self.return_mapped(map_func(job.chunks))
      elif (job.pairs):
        reduce_func(job)