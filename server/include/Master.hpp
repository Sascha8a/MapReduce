#pragma once

#include <grpcpp/grpcpp.h>
#include <thread>
#include <map>

#include "FIFOScheduler.hpp"
#include "JobTracker.hpp"
#include "internal.grpc.pb.h"
#include "internal.pb.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

/**
 * @brief This class is the central unit of the MapReduce cluster. It's job is to coordinate.
 * See documentation for more information.
 */
class Master final : public mapreduce::Master::Service
{
private:
  bool _debug{false};
  std::vector<std::string> _nodes;
  std::shared_ptr<spdlog::logger> _console{spdlog::stderr_color_mt("Master")};
  FIFOScheduler _scheduler;
  long _new_job_id{1};
  std::unordered_map<long, JobTracker> _job_trackers{};
public:
  Master(bool debug);

  /**
   * @brief Returns the current status of a particular job
   * 
   * @param job_id  ID of the job
   * @return mapreduceAPI::JobStatus Status 
   */
  mapreduceAPI::JobStatus get_status(long job_id);

  /**
   * @brief Get the results of a jbo
   * 
   * @param job_id The id of the job
   * @return std::vector<std::pair<std::string, long>> Returns a vector of key-value (string, long) pairs.
   */
  std::vector<std::pair<std::string, long>> get_results(long job_id);

  /**
   * @brief Delete a particular job.  
   * 
   * @param job_id THe id of the job
   */
  void clear_results(long job_id);

  /**
   * @brief Start a new job
   * 
   * @param chunks A, already splitted, vector of strings to be processed
   * @param code The code that is run on every node
   * @return long The id of the job
   */
  long StartJob(std::vector<std::string> chunks, std::string code);

  /**
   * @brief Called by nodes (see documentation). Registeres a new node to the scheduler
   */
  grpc::Status RegisterNode(grpc::ServerContext *context, const mapreduce::NewNode *node, mapreduce::Empty *response) override;

  /**
   * @brief Called by nodes (see documentation). Receives the results of a task and processes them.
   */
  grpc::Status TaskDone(grpc::ServerContext *context, const mapreduce::Task *task, mapreduce::Empty *response) override;
};
