import grpc
import internal_pb2
import internal_pb2_grpc

class Worker():
  def __init__(self, map_func, reduce_func):
    with grpc.insecure_channel('localhost:50051') as channel:
      stub = internal_pb2_grpc.NodeStub(channel)
      job = stub.GetJob(internal_pb2.JobRequest(job_id="aaa"))

