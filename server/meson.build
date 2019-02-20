# uncomment as necessary
project('MapReduce', 'cpp',
        license : ['Boost'],
        version : '0.1',
        default_options : ['cpp_std=c++14', 'warning_level=3', 'werror=true'])

thread_dep = dependency('threads')

# # begin asio: https://think-async.com/Asio/
# add_global_arguments('-I' + get_option('asio_include_dir'), language : 'cpp')
# add_global_arguments('-DASIO_STANDALONE', language : 'cpp')
# add_global_arguments('-DASIO_NO_DEPRECATED', language : 'cpp')
# # end asio

# clipp: https://github.com/muellan/clipp/
# add_global_arguments('-I' + get_option('clipp_include_dir'), language : 'cpp')

# CLI11: https://github.com/CLIUtils/CLI11
# add_global_arguments('-I' + get_option('cli11_include_dir'), language : 'cpp')

# spdlog: https://github.com/gabime/spdlog
add_global_arguments('-I' + get_option('spdlog_include_dir'), language : 'cpp')

# json: https://github.com/nlohmann/json
# add_global_arguments('-I' + get_option('json_include_dir'), language : 'cpp')

# begin protobuf: https://developers.google.com/protocol-buffers/
# protobuf: must be installed independently and has to be found...
protoc = find_program('protoc', required : true)
python3 = find_program('python3', required : true)
grpc_cpp_plugin = find_program('grpc_cpp_plugin', required : true)
grpc_python_plugin = find_program('grpc_python_plugin', required : true)
protobuf_dep = dependency('protobuf', required : true)
grpc_dep = dependency('grpc', required : true)
grpcpp_dep = dependency('grpc++', required : true)

gen = generator(protoc, \
  output    : ['@BASENAME@.pb.cc', '@BASENAME@.pb.h', '@BASENAME@.grpc.pb.cc', '@BASENAME@.grpc.pb.h'],
  arguments : ['--proto_path=@SOURCE_DIR@/src/protos',
                '--plugin=protoc-gen-grpc=' + grpc_cpp_plugin.path(),
               '--grpc_out=@BUILD_DIR@',
               '--cpp_out=@BUILD_DIR@',
               '../src/protos/@PLAINNAME@'])

gen_py = generator(python3, \
  output    : ['@BASENAME@_pb2.py', '@BASENAME@_pb2_grpc.py'],
  arguments : ['-mgrpc_tools.protoc',
               '--proto_path=@SOURCE_DIR@/src/protos',
               '--grpc_python_out=@SOURCE_DIR@',
               '--python_out=@SOURCE_DIR@',
               '../src/protos/@PLAINNAME@'])

# change proto file accordingly
internal_proto = gen.process('src/protos/internal.proto')
internal_proto_py = gen_py.process('src/protos/internal.proto')
# end protobuf

# subdir('SUBDIR1')

inc_dir = include_directories('include')
master_src = ['src/master.cpp', 'src/Master.cpp', internal_proto, internal_proto_py]
node_src = ['src/node.cpp', 'src/Node.cpp', internal_proto, internal_proto_py]
cli_src = ['src/cli.cpp', internal_proto, internal_proto_py]

executable('master',
           sources : master_src,
           include_directories : inc_dir,
           dependencies : [thread_dep, protobuf_dep, grpc_dep, grpcpp_dep]
          )

executable('node',
           sources : node_src,
           include_directories : inc_dir,
           dependencies : [thread_dep, protobuf_dep, grpc_dep, grpcpp_dep]
          )

executable('cli',
           sources : cli_src,
           include_directories : inc_dir,
           dependencies : [thread_dep, protobuf_dep, grpc_dep, grpcpp_dep]
          )