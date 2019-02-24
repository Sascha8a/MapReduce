#pragma once

#include <grpcpp/grpcpp.h>
#include <map>
#include <vector>

#include "internal.grpc.pb.h"
#include "internal.pb.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

class Node final : public mapreduce::Node::Service
{
private:
  std::string _chunk;
  long _task_id;
  long _job_id;
  std::string _master_uri;
  std::string _own_uri;
  std::shared_ptr<spdlog::logger> _console{spdlog::stderr_color_mt("Node")};

public:
  Node(std::string node_uri) {
    _own_uri = node_uri;
    _console->set_level(spdlog::level::debug); //TODO: Config
  }
  grpc::Status JobGet(grpc::ServerContext *context, const mapreduce::Empty *request, mapreduce::Job *response) override;
  grpc::Status JobMapped(grpc::ServerContext *context, const mapreduce::MappedJob *job, mapreduce::Empty *response) override;
  grpc::Status StartTask(grpc::ServerContext *context, const mapreduce::Task *task, mapreduce::Empty *response) override;
  std::string write_code_file(const long id, const mapreduce::CodeExt ext, const std::string code);
  void start_code_file(const mapreduce::CodeExt ext, const std::string code_localtion);
  void register_at_master(std::string uri);
};
