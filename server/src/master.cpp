#include <iostream>
#include <sstream>
#include <fstream>
#include <thread>
#include <grpcpp/grpcpp.h>
#include <iostream>

#include "APIServer.hpp"
#include "internal.grpc.pb.h"
#include "internal.pb.h"
#include "Master.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

int main()
{
  std::string server_address("0.0.0.0:50050"); //TODO: Config file, CLI

  Master service;
  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  spdlog::info("Master: " + server_address);

  APIServer api{3000, &service};

  server->Wait();

  return 0;
}
