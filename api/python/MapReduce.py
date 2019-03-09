import grpc
import internal_pb2
import internal_pb2_grpc
import sys

class Worker:
    def __init__(self, map_func, reduce_func):
        with grpc.insecure_channel(sys.argv[1]) as channel:
            stub = internal_pb2_grpc.NodeStub(channel)
            job = stub.JobGet(internal_pb2.Empty())

            if (job.chunk):
                self.return_mapped(map_func(job.chunk), job.id)
            elif (job.key):
                self.return_reduced(reduce_func(job.key, job.value), job.id, job.key)

    def return_mapped(self, result, job_id):
        with grpc.insecure_channel(sys.argv[1]) as channel:

            results_message = internal_pb2.MappedJob()
            results_message.id = job_id
            for obj in result:
                new_entry = results_message.pairs.add()
                new_entry.key = obj[0]
                new_entry.value = obj[1]

            stub = internal_pb2_grpc.NodeStub(channel)
            stub.JobMapped(results_message)

    def return_reduced(self, result, job_id, job_key):
        with grpc.insecure_channel(sys.argv[1]) as channel:

            results_message = internal_pb2.ReducedJob()
            results_message.id = job_id
            results_message.key = job_key
            results_message.result = result

            stub = internal_pb2_grpc.NodeStub(channel)
            stub.JobReduced(results_message)