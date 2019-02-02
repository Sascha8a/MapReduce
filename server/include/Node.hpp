#pragma once

#include <grpcpp/grpcpp.h>
#include <map>
#include <vector>

#include "internal.grpc.pb.h"
#include "internal.pb.h"

class Node final : public mapreduce::Node::Service
{
private:
  std::map<std::string, mapreduce::Job> _jobs;
  std::map<std::string, u_int8_t> _workers;
  std::map<std::string, std::vector<mapreduce::KeyValuePair>> _mapresults;

public:
  grpc::Status JobStart(grpc::ServerContext *context, const mapreduce::Job *job, mapreduce::Empty *response) override;
  grpc::Status JobGet(grpc::ServerContext *context, const mapreduce::JobRequest *request, mapreduce::Job *response) override;
  grpc::Status JobMapped(grpc::ServerContext *context, const mapreduce::MappedJob *request, mapreduce::Empty *response) override;
};
