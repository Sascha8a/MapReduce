#pragma once

#include <string>
#include <vector>

#include "FIFOScheduler.hpp"
#include "internal.grpc.pb.h"
#include "internal.pb.h"
#include "API.grpc.pb.h"
#include "API.pb.h"

/**
 * @brief The purpose of this class is to track the current status of one particular job.
 * It stores it's results, creates tasks etc..
 * See documentation for more info
 * 
 */
class JobTracker
{
private:
  long _job_id;
  long _map_tasks_left;
  long _reduce_tasks_left;
  std::vector<std::pair<std::string, long>> _results;
  std::string _code;
  FIFOScheduler* _scheduler;
  std::vector<std::string> _input;
  std::unordered_map<std::string, std::vector<long>> _map_results;
  std::vector<std::string> _map_keys;
  std::shared_ptr<spdlog::logger> _console;

  /**
   * @brief Creates and adds all tasks necessary for the map phase
   * 
   */
  void start_map();

  /**
   * @brief Creates and adds all tasks of the reduce phase
   * 
   */
  void start_reduce();

public:
  mapreduceAPI::JobStatus get_status();
  std::vector<std::pair<std::string, long>>  get_results();
  JobTracker(long id, FIFOScheduler* scheduler, std::vector<std::string> chunks, std::string code);
  ~JobTracker() {};

  /**
   * @brief Call this function once a job has been mapped
   * 
   */
  void mapped(mapreduce::MappedJob);

    /**
   * @brief Call this function once a job has been reduced
   * 
   */
  void reduced(mapreduce::ReducedJob);
};
