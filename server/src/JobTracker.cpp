#include "JobTracker.hpp"

#include "internal.grpc.pb.h"
#include "internal.pb.h"

void JobTracker::start_map()
{
  for (std::string const &chunk : _input)
  {
    mapreduce::MapJob job;
    job.set_code(_code);
    job.set_ext(mapreduce::CodeExt::py); //TODO: Dynamic
    job.set_job_id(_job_id);
    job.set_chunk(chunk);
    _scheduler->add_task(job.SerializeAsString());
  }

  _map_tasks_left = _input.size();
  _input.clear();
}

void JobTracker::start_reduce()
{
  _map_results.
}

void JobTracker::mapped(mapreduce::MappedJob m_job)
{
  _console->debug("Pushing map result");

  for (mapreduce::KeyValuePair const &pair : m_job.pairs())
  {
    if (!_map_results[pair.key()].size()) {
      _map_keys.push_back(pair.key());
    }
    _map_results[pair.key()].push_back(pair.value());
  }

  _map_tasks_left -= 1;

  if (!_map_tasks_left)
  {
    _console->info("Map phase done");
    start_reduce();
  }
}

JobTracker::JobTracker(long id, FIFOScheduler *scheduler, std::vector<std::string> input, std::string code)
{
  _console = spdlog::stderr_color_mt("JobTracker " + std::to_string(id));

  _scheduler = scheduler;
  _job_id = id;
  _input = input;
  _code = code;

  start_map();
}