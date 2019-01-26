using namespace std;

#include <iostream>

#include "CLI11.hpp"

void fn_master_start()
{
  cout << "start" << endl;
}

void fn_master_stop()
{
  cout << "stop" << endl;
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
  CLI::App *master_logs = master_cli->add_subcommand("logs", "Stream the log");
  master_logs->callback(*fn_master_logs_stream);
  // CLI::App *jobs_cli = map_reduce_cli.add_subcommand("jobs", "A set of commands for monitoring jobs.");
  // CLI::App *jobs_cli = map_reduce_cli.add_subcommand("node", "A set of commands for node management.");

  CLI11_PARSE(map_reduce_cli, argc, argv);
  return 0;
}
