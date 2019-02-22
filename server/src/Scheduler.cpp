#include <grpcpp/grpcpp.h>

#include "spdlog/spdlog.h"
#include "internal.grpc.pb.h"
#include "internal.pb.h"

#include "Scheduler.hpp"

void Scheduler::send_to_node(Task t, SchedulerNode node)
{
  _console->info("Sending Task " + std::to_string(t.id) + " to " + node.connstr);

  auto channel{grpc::CreateChannel(node.connstr, grpc::InsecureChannelCredentials())};
  auto stub{mapreduce::Node::NewStub(channel)};

  _console->info("Task sent");
}