import grpc
import internal_pb2
import internal_pb2_grpc
import json
import sys
import Worker

def map_func(chunk):
    results = []

    for word in str(chunk).split(' '):
        results.append([word, 1])

    return results


def reduce_func(key, values):
    return sum(values)


worker = Worker(map_func, reduce_func)
