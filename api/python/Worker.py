import grpc
import internal_pb2
import internal_pb2_grpc
import json
import sys

class Worker:
    def return_mapped(self, result, job_id):
        with grpc.insecure_channel('localhost:50051') as channel:

            results_message = internal_pb2.MappedJob()
            results_message.id = job_id
            for obj in result:
                new_entry = results_message.pairs.add()
                new_entry.key = obj[0]
                new_entry.value = obj[1]

            stub = internal_pb2_grpc.NodeStub(channel)
            stub.JobMapped(results_message)

    def __init__(self, map_func, reduce_func):
        with grpc.insecure_channel(sys.argv[1]) as channel:
            stub = internal_pb2_grpc.NodeStub(channel)
            job = stub.JobGet(internal_pb2.Empty())

            if (job.chunk):
                self.return_mapped(map_func(job.chunk), job.id)
            elif (job.pairs):
                reduce_func(job)
