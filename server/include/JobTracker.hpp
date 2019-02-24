#pragma once

#include <string>
#include <vector>

#include "FIFOScheduler.hpp"

class JobTracker
{
private:
  long _job_id;
  std::string _code;
  FIFOScheduler* _scheduler;
  std::vector<std::string> _input;
  void start_map();

public:
  JobTracker(long id,FIFOScheduler* scheduler, std::vector<std::string> chunks, std::string code);
  ~JobTracker() {};
};
