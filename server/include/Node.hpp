#pragma once

#include <grpcpp/grpcpp.h>

#include "internal.grpc.pb.h"
#include "internal.pb.h"

class Node final : public mapreduce::Node::Service
{
public:
  grpc::Status StartJob(grpc::ServerContext *context, const mapreduce::Job *job, mapreduce::Empty *response) override;
};
