# THIS DOESN'T RUN!

def mapper(chunk): # defaults to string of lines
  return results # {string: any}

def reducer(kv): # {string: [any]}
  return results # {string: any}

job = new Job(
  input = [url, ur2, ...]
  map = mapper
  reduce = reducer
  master? = "localhost"
  nodes? = #all
)