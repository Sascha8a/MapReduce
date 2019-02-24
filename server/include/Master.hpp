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
  std::vector<std::string> _nodes;
  std::shared_ptr<spdlog::logger> _console{spdlog::stderr_color_mt("Master")};
  FIFOScheduler _scheduler{};
  std::map<long, JobTracker> _job_trackers;
public:
  Master();
  grpc::Status RegisterNode(grpc::ServerContext *context, const mapreduce::NewNode *node, mapreduce::Empty *response) override;
  grpc::Status JobStart(grpc::ServerContext *context, const mapreduce::NewJob *job, mapreduce::Empty *response) override;
};
