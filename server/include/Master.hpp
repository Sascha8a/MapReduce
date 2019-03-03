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
  mapreduceAPI::JobStatus get_status(long job_id);
  std::vector<std::pair<std::string, long>> get_results(long job_id);
  void clear_results(long job_id);
  long StartJob(std::vector<std::string> chunks, std::string code);
  grpc::Status RegisterNode(grpc::ServerContext *context, const mapreduce::NewNode *node, mapreduce::Empty *response) override;
  grpc::Status JobStart(grpc::ServerContext *context, const mapreduce::NewJob *job, mapreduce::Empty *response) override;
  grpc::Status TaskDone(grpc::ServerContext *context, const mapreduce::Task *task, mapreduce::Empty *response) override;
};
