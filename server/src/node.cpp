#include <iostream>
#include <thread>
#include <grpcpp/grpcpp.h>
#include <iostream>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "internal.grpc.pb.h"
#include "internal.pb.h"

#include "Node.hpp"

int main()
{
  spdlog::stderr_color_mt("console");

  Node service{"localhost:50051"};

  grpc::ServerBuilder builder;
  builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

  service.register_at_master("127.0.0.1:50050"); //TODO: Config
  server->Wait();

  return 0;
}
