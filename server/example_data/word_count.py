from MapReduce import Worker

def map_func(chunk):
    results = []

    for word in str(chunk).split(' '):
        results.append([word, 1])

    return results


def reduce_func(key, values):
    return sum(values)

Worker(map_func, reduce_func)
