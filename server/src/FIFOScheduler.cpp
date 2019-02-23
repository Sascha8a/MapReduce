#include <grpcpp/grpcpp.h>
#include <iostream>
#include <thread>
#include <chrono>

#include "FIFOScheduler.hpp"
#include "internal.grpc.pb.h"
#include "internal.pb.h"

FIFOScheduler::FIFOScheduler()
{
  
}

void FIFOScheduler::send_to_node(Task t, SchedulerNode node)
{
  _console->info("Sending Task " + std::to_string(t.id) + " to " + node.connstr);

  auto channel{grpc::CreateChannel(node.connstr, grpc::InsecureChannelCredentials())};
  auto stub{mapreduce::Node::NewStub(channel)};

  grpc::ClientContext context;
  mapreduce::Empty response;
  mapreduce::Task t_msg;
  t_msg.set_id(t.id);
  t_msg.set_job(t.job);
  grpc::Status status{stub->StartTask(&context, t_msg, &response)};

  if (status.ok())
  {
    _console->info("Task " + std::to_string(t.id) + " delivered");
  } else {
    _console->error("Error delivering task " + std::to_string(t.id) + ": " + status.error_message());
  }
}

void FIFOScheduler::update()
{
  if (!_free_nodes.size())
    return;
  if (!_tasks.size())
    return;

  Task task{_tasks.front()};
  _tasks.pop();

  std::unique_lock<std::mutex> lock{_node_mutex};
  
  SchedulerNode node{_free_nodes.front()};
  _free_nodes.pop();
  _full_nodes[task.id] = node;

  lock.release();

  send_to_node(task, node);
}

void FIFOScheduler::operator()()
{
  _console->info("Started");

  while (1)
  {
    update();
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

void FIFOScheduler::add_node(std::string connstr)
{
  SchedulerNode new_node;
  new_node.connstr = connstr;
  new_node.free = true;

  std::unique_lock<std::mutex> lock{_node_mutex};

  _free_nodes.push(new_node);
}

void FIFOScheduler::add_task(Task task)
{
  _tasks.push(task);
}

void FIFOScheduler::task_done(Task task)
{
  std::unique_lock<std::mutex> lock{_node_mutex};

  auto node{_full_nodes[task.id]};
  _full_nodes.erase(task.id);
  _free_nodes.push(node);

  std::cout << std::to_string(task.id) << std::endl;
}