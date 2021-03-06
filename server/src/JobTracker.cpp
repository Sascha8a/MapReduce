#include "JobTracker.hpp"
#include "internal.grpc.pb.h"
#include "internal.pb.h"

mapreduceAPI::JobStatusResponse JobTracker::get_status()
{
  mapreduceAPI::JobStatusResponse response;

  if (_map_tasks_left)
  {
    response.set_map_tasks(_map_tasks);
    response.set_map_tasks_remaining(_map_tasks_left);
    response.set_status(mapreduceAPI::JobStatus::map_phase);
  }
  else if (_reduce_tasks_left)
  {
    response.set_reduce_tasks(_reduce_tasks);
    response.set_reduce_tasks_remaining(_reduce_tasks_left);
    response.set_status(mapreduceAPI::JobStatus::reduce_phase);
  }
  else
  {
    response.set_status(mapreduceAPI::JobStatus::finished);
  }

  return response;
}

std::vector<std::pair<std::string, long>> JobTracker::get_results()
{
  return _results;
}

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
  _map_tasks = _input.size();
  _input.clear();
}

void JobTracker::start_reduce()
{
  for (std::string const &key : _map_keys)
  {
    mapreduce::ReduceJob job;
    job.set_code(_code);
    job.set_ext(mapreduce::CodeExt::py); //TODO: Dynamic
    job.set_job_id(_job_id);
    job.set_key(key);

    for (int const &value : _map_results[key])
    {
      job.add_value(value);
    }

    _scheduler->add_task(job.SerializeAsString());
  }
  _reduce_tasks_left = _map_keys.size();
  _reduce_tasks = _map_keys.size();
  _map_results.clear();
  _map_keys.clear();
}

bool JobTracker::map_phase_done()
{
  return _map_tasks_left <= 0;
}

void JobTracker::mapped(mapreduce::MappedJob m_job)
{
  _console->debug("Pushing map result");

  for (mapreduce::KeyValuePair const &pair : m_job.pairs())
  {
    if (!_map_results[pair.key()].size())
    {
      _map_keys.push_back(pair.key());
    }
    _map_results[pair.key()].push_back(pair.value());
  }

  _map_tasks_left -= 1;
  _console->info("Map tasks left: {}", std::to_string(_map_tasks_left));

  if (!_map_tasks_left)
  {
    _console->info("Map phase done");
    start_reduce();
  }
}

void JobTracker::reduced(mapreduce::ReducedJob job)
{
  _results.push_back(std::make_pair(job.key(), job.result()));
  _reduce_tasks_left -= 1;
  _console->info("Reduce tasks left:  {}", std::to_string(_reduce_tasks_left));

  if (!_reduce_tasks_left)
  {
    _console->info("Reduce phase done");
    _console->info("Job finished");
  }
}

JobTracker::JobTracker(long id, FIFOScheduler *scheduler, std::vector<std::string> input, std::string code)
{
  _console = spdlog::stderr_color_mt(fmt::format("JobTracker {}", id));

  _scheduler = scheduler;
  _job_id = id;
  _input = input;
  _code = code;

  start_map();
}