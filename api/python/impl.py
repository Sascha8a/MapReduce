from Worker import Worker

def map_func(chunk):
  return {"a": 5, "b": 1}

def reduce_func(kvs):
  return {"a": 5}

worker = Worker(map_func, reduce_func)