#include <grpcpp/grpcpp.h>
#include <iostream>
#include <thread>
#include <chrono>

#include "FIFOScheduler.hpp"
#include "internal.grpc.pb.h"
#include "internal.pb.h"

FIFOScheduler::FIFOScheduler(bool debug)
{
  if (debug)
  {
    _console->set_level(spdlog::level::debug);
  }
}

void FIFOScheduler::send_to_node(Task t, SchedulerNode node)
{
  std::thread thread{[t, node](){
    auto channel{grpc::CreateChannel(node.connstr, grpc::InsecureChannelCredentials())};
    auto stub{mapreduce::Node::NewStub(channel)};

    grpc::ClientContext context;
    mapreduce::Empty response;
    mapreduce::Task t_msg;
    t_msg.set_id(t.id);
    t_msg.set_job(t.job);
    grpc::Status status{stub->StartTask(&context, t_msg, &response)};
  }};

  thread.detach();
}

void FIFOScheduler::update()
{
  if (!_free_nodes.size_approx())
  {
    // _console->debug("No free nodes");
    return;
  }

  if (!_tasks.size_approx())
  {
    // _console->debug("No tasks");
    return;
  }

  _console->debug("Processing task");

  Task task;
  bool found_task{_tasks.try_dequeue(task)};

  if (!found_task)
  {
    return;
  }

  SchedulerNode node;
  bool found_node{_free_nodes.try_dequeue(node)};

  if (!found_node)
  {
    _tasks.enqueue(task);
    return;
  }

  _full_nodes[task.id] = node;
  send_to_node(task, node);
}

void FIFOScheduler::operator()()
{
  _console->info("Started");

  while (true)
  {
    update();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

void FIFOScheduler::add_node(std::string connstr)
{
  SchedulerNode new_node;
  new_node.connstr = connstr;
  new_node.free = true;
  _free_nodes.enqueue(new_node);

  _console->info("Node added: {}", connstr);
}

void FIFOScheduler::add_task(Task task)
{
  _tasks.enqueue(task);
  _console->debug("New task added: {}", std::to_string(task.id));
}

void FIFOScheduler::add_task(std::string job)
{
  Task task;
  task.id = _new_task_id;
  _new_task_id += 1;
  task.job = job;

  add_task(task);
}

void FIFOScheduler::task_done(long id)
{
  auto node{_full_nodes[id]};
  _full_nodes.erase(id);
  _free_nodes.enqueue(node);

  _console->debug("Task done: {}", std::to_string(id));
}