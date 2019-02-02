import grpc
import internal_pb2
import internal_pb2_grpc
import json


class Worker:
    def return_mapped(self, result):
        with grpc.insecure_channel('localhost:50051') as channel:

            results_message = internal_pb2.MappedJob()
            results_message.job_id = "aaa"

            for obj in result:
                new_entry = results_message.pairs.add()
                new_entry.key = obj[0]
                new_entry.value = obj[1]

            stub = internal_pb2_grpc.NodeStub(channel)
            stub.JobMapped(results_message)

    def __init__(self, map_func, reduce_func):
        with grpc.insecure_channel('localhost:50051') as channel:
            stub = internal_pb2_grpc.NodeStub(channel)
            job = stub.JobGet(internal_pb2.JobRequest(job_id="aaa"))

            if (job.chunks):
                self.return_mapped(map_func(job.chunks[0]))
            elif (job.pairs):
                reduce_func(job)
