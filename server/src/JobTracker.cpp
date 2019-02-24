#include "JobTracker.hpp"

#include "internal.grpc.pb.h"
#include "internal.pb.h"

void JobTracker::start_map()
{
  for(std::string const& chunk : _input) {
    mapreduce::MapJob job;
    job.set_code(_code);
    job.set_ext(mapreduce::CodeExt::py); //TODO: Dynamic
    job.set_job_id(_job_id);
    job.set_chunk(chunk);
    _scheduler->add_task(job.SerializeAsString());
  }
}

JobTracker::JobTracker(long id, FIFOScheduler* scheduler, std::vector<std::string> input, std::string code)
{
  _scheduler = scheduler;
  _job_id = id;
  _input = input;
  _code = code;

  start_map();
}