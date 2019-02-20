#include "Master.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "internal.grpc.pb.h"
#include "internal.pb.h"

Master::Master()
{
  _console->set_level(spdlog::level::debug);
}

grpc::Status Master::RegisterNode(grpc::ServerContext *context, const mapreduce::NewNode *node, mapreduce::Empty *response)
{
  _console->info("New connection fron Node " + context->peer());
  auto channel{grpc::CreateChannel(node->connstr(), grpc::InsecureChannelCredentials())};
  auto stub{mapreduce::Node::NewStub(channel)};

  _nodes.push_back(node->connstr());

  _console->info("Connection established.");

  response->Clear();
  return grpc::Status::OK;
}

grpc::Status Master::JobStart(grpc::ServerContext *context, const mapreduce::NewJob *job, mapreduce::Empty *response)
{
  _console->info("New job from " + context->peer());
  _console->debug("Job data\n" + job->data());
  _console->debug("Job data end");
  response->Clear();
  return grpc::Status::OK;
}
