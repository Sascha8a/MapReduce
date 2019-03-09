#include <iostream>
#include <thread>
#include <grpcpp/grpcpp.h>
#include <iostream>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "internal.grpc.pb.h"
#include "internal.pb.h"
#include "Node.hpp"
#include "CLI11.hpp"

#define MIN_PORT 3100
#define MAX_PORT 3200
static gpr_atm s_pick_counter = 0;

/**
 * Source: https://github.com/grpc/grpc/blob/ea232d16d37b8e88806fca3843a360cc338d1a17/test/core/util/port_isolated_runtime_environment.cc#L36-L41
 **/
static int get_random_port_offset()
{
  srand(gpr_now(GPR_CLOCK_REALTIME).tv_nsec);
  double rnd = static_cast<double>(rand()) /
               (static_cast<double>(RAND_MAX) + 1.0); // values from [0,1)
  return static_cast<int>(rnd * (MAX_PORT - MIN_PORT + 1));
}

/**
 * Source: https://github.com/grpc/grpc/blob/ea232d16d37b8e88806fca3843a360cc338d1a17/test/core/util/port_isolated_runtime_environment.cc#L43-L52
 **/
int grpc_pick_unused_port(void)
{
  int orig_counter_val =
      static_cast<int>(gpr_atm_full_fetch_add(&s_pick_counter, 1));
  GPR_ASSERT(orig_counter_val < (MAX_PORT - MIN_PORT + 1));
  return MIN_PORT +
         (get_random_port_offset() + orig_counter_val) % (MAX_PORT - MIN_PORT + 1);
}

bool file_exists(std::string file_uri)
{
  std::ifstream file{file_uri};
  return file.good();
}

int main(int argc, char **argv)
{
  CLI::App app{"'Worker' part of the MapReduce project"};

  std::string port{std::to_string(grpc_pick_unused_port())};
  app.add_option("-p,--port", port, "The port of this node; Random by default");

  std::string masteruri{"127.0.0.1:50050"};
  app.add_option("-m,--master", masteruri, "Connection string to the master; 127.0.0.1:50050 by default");

  bool debug{false};
  app.add_flag("-d,--debug", debug, "Enable debug output");

  CLI11_PARSE(app, argc, argv);

  if (!file_exists("tmp/MapReduce.py"))
  {
    spdlog::error("Missing tmp/MapReduce.py");
    std::exit(1);
  }

  if (!file_exists("tmp/internal_pb2_grpc.py"))
  {
    spdlog::error("Missing tmp/internal_pb2_grpc.py");
    std::exit(1);
  }

  if (!file_exists("tmp/internal_pb2.py"))
  {
    spdlog::error("Missing tmp/internal_pb2.py");
    std::exit(1);
  }

  grpc::ServerBuilder builder;
  Node service{"localhost:" + port, debug};
  builder.AddListeningPort("0.0.0.0:" + port, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

  try
  {
    service.register_at_master(masteruri);
    spdlog::info("Listening on port " + port);
    server->Wait();
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';

    return 1;
  }

  return 0;
}
