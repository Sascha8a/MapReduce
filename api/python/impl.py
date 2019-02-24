from Worker import Worker

# job.add_chunks("a a b b c c"); // a:2 b:2 c:2
# job.add_chunks("a b c");       // a:1 b:1 c:1
# job.add_chunks("a");           // a:1
#                               // a:4 b:3 c:3


def map_func(chunk):
    results = []

    for word in str(chunk).split(' '):
        results.append([word, 1])

    return results


def reduce_func(key, values):
    return sum(values)


worker = Worker(map_func, reduce_func)
