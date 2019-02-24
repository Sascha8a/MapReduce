#pragma once

#include <string>
#include <vector>

#include "FIFOScheduler.hpp"
#include "internal.grpc.pb.h"
#include "internal.pb.h"

class JobTracker
{
private:
  long _job_id;
  long _map_tasks_left;
  std::string _code;
  FIFOScheduler* _scheduler;
  std::vector<std::string> _input;
  std::unordered_map<std::string, std::vector<long>> _map_results;
  std::vector<std::string> _map_keys;

  std::shared_ptr<spdlog::logger> _console;
  void start_map();
  void start_reduce();

public:
  JobTracker(long id, FIFOScheduler* scheduler, std::vector<std::string> chunks, std::string code);
  ~JobTracker() {};
  void mapped(mapreduce::MappedJob);
};
