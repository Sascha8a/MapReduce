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

  std::string server_address("0.0.0.0:50051");
  Node service;

  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

  std::cout << "Node: " << server_address << std::endl;

  server->Wait();

  return 0;
}
