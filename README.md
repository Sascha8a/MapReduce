# MapReduce
====

## Usage


1. Preparations
```sh
cd server && mkdir build && cd build
meson .. && ninja
cp -R ../example_data/* .
```

2. Master

```sh
./master
```

2. Node(s)

```sh
./node
```

3. Job


```sh
./cli start --config job.json
```

4. Status

```sh
./cli status --id 1
```

5. Profit
