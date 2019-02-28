using namespace std;

#include <iostream>
#include <grpcpp/grpcpp.h>

#include "internal.grpc.pb.h"
#include "internal.pb.h"
#include "CLI11.hpp"

std::string get_file(std::string filename)
{
  std::ifstream fstream;
  std::stringstream sstream;

  fstream.open(filename);
  sstream << fstream.rdbuf();

  return sstream.str();
}

void fn_master_start()
{
  cout << "start" << endl;
}

void fn_master_stop()
{
  cout << "stop" << endl;
}

void fn_master_test()
{
  auto channel{grpc::CreateChannel("localhost:50050", grpc::InsecureChannelCredentials())};
  auto stub = mapreduce::Master::NewStub(channel);

  mapreduce::NewJob job;

  const string code{get_file("impl.py")};
  job.set_code(code);
  const string data{get_file("shakespeare.txt")};
  job.set_data(data);

  grpc::ClientContext context;
  mapreduce::Empty response;
  grpc::Status status{stub->JobStart(&context, job, &response)};

  if (status.ok()) {
    cout << "Job sent" << endl;
  } else {
    cout << status.error_message() << endl;
  }

}

void fn_master_logs_stream()
{
  cout << "Stream" << endl;
}

void fn_todo()
{
  cout << "TODO" << endl;
}

int main(int argc, char *argv[])
{
  CLI::App map_reduce_cli{"CLI for the mapreduce project", "CLI"};
  map_reduce_cli.failure_message(CLI::FailureMessage::help);
  map_reduce_cli.require_subcommand(1);

  // CLI Master section
  CLI::App *master_cli = map_reduce_cli.add_subcommand("master", "Manage the master instance");
  master_cli->require_subcommand(1);
  CLI::App *master_start = master_cli->add_subcommand("start", "Start a new instance");
  master_start->callback(*fn_master_start);
  CLI::App *master_stop = master_cli->add_subcommand("stop", "Stop the instance");
  master_stop->callback(*fn_master_stop);
  CLI::App *master_test = master_cli->add_subcommand("test", "Tests master instance functionality with a simple test");
  master_test->callback(*fn_master_test);
  CLI::App *master_logs = master_cli->add_subcommand("logs", "Stream the log");
  master_logs->callback(*fn_master_logs_stream);
  // CLI::App *jobs_cli = map_reduce_cli.add_subcommand("jobs", "A set of commands for monitoring jobs.");
  // CLI::App *jobs_cli = map_reduce_cli.add_subcommand("node", "A set of commands for node management.");

  CLI11_PARSE(map_reduce_cli, argc, argv);
  return 0;
}
