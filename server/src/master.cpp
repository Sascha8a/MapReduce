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
#include "CLI11.hpp"

int main(int argc, char** argv)
{
  CLI::App app{"Controller for the MapReduce project"};

  std::string port{"50050"};
  app.add_option("-p,--port", port, "The port of this master; 50050 by default");

  std::string api_port{"3000"};
  app.add_option("-a,--apiport", api_port, "The port the API should run on; 3000 by default");

  bool debug{false};
  app.add_flag("-d,--debug", debug, "Enable debug output");

  int num_schedulers{2};
  app.add_option("-s,--schedulers", num_schedulers, "Number of scheduler threads");


  CLI11_PARSE(app, argc, argv);

  std::string server_address(fmt::format("0.0.0.0:{}", port));

  Master service{debug, num_schedulers};
  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  spdlog::info("Master: {}", server_address);

  APIServer api{std::atoi(api_port.c_str()), &service, debug};

  server->Wait();

  return 0;
}
