import Worker

def map_func(chunk):
    result_dict = {}
    results = []

    for word in str(chunk).split(' '):
        if (result_dict[word]):
            result_dict[word] += 1
        else:
            result_dict[word] = 1

    for key, value in result_dict.items():
        results.append([key, value])

    return results

def reduce_func(key, values):
    return sum(values)


worker = Worker(map_func, reduce_func)n
