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
  std::map<std::string, mapreduce::Job> _jobs;
  std::map<std::string, u_int8_t> _workers;
  std::string _chunk;
  std::map<std::string, std::vector<mapreduce::KeyValuePair>> _mapresults;
  std::string _master_uri;
  std::shared_ptr<spdlog::logger> _console{spdlog::stderr_color_mt("Node")};

public:
  Node() {
    _console->set_level(spdlog::level::debug); //TODO: Config
  }
  grpc::Status JobGet(grpc::ServerContext *context, const mapreduce::Empty *request, mapreduce::Job *response) override;
  grpc::Status StartTask(grpc::ServerContext *context, const mapreduce::Task *task, mapreduce::Empty *response) override;
  std::string write_code_file(const long id, const mapreduce::CodeExt ext, const std::string code);
  void start_code_file(const mapreduce::CodeExt ext, const std::string code_localtion);
  void register_at_master(std::string uri);
};
