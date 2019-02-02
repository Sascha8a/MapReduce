#pragma once

#include <grpcpp/grpcpp.h>
#include <map>

#include "internal.grpc.pb.h"
#include "internal.pb.h"

class Node final : public mapreduce::Node::Service
{
private:
  std::map<std::string, mapreduce::Job> _jobs;

public:
  grpc::Status StartJob(grpc::ServerContext *context, const mapreduce::Job *job, mapreduce::Empty *response) override;
  grpc::Status GetJob(grpc::ServerContext *context, const mapreduce::JobRequest *request, mapreduce::Job *response) override;
  grpc::Status MappedJob(grpc::ServerContext *context, const mapreduce::MapResults *request, mapreduce::Empty *response) override;
};
