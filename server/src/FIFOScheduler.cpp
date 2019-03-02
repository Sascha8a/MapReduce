#include <grpcpp/grpcpp.h>
#include <iostream>
#include <thread>
#include <chrono>

#include "FIFOScheduler.hpp"
#include "internal.grpc.pb.h"
#include "internal.pb.h"

FIFOScheduler::FIFOScheduler()
{
  _console->set_level(spdlog::level::debug); //TODO: Config
}

void FIFOScheduler::send_to_node(Task t, SchedulerNode node)
{
  _console->debug("Sending Task " + std::to_string(t.id) + " to " + node.connstr);

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
    _console->debug("Task " + std::to_string(t.id) + " delivered");
  } else {
    _console->error("Error delivering task " + std::to_string(t.id) + ": " + status.error_message());
  }
}

void FIFOScheduler::update()
{
  if (!_free_nodes.size()) {
    _console->debug("All nodes busy");
    return;
  }

  if (!_tasks.size()) {
    _console->debug("No tasks to process");
    return;
  }

  Task task{_tasks.front()};
  _tasks.pop();

  std::lock_guard<std::mutex> lock(_node_mutex);
  
  SchedulerNode node{_free_nodes.front()};
  _free_nodes.pop();
  _full_nodes[task.id] = node;

  send_to_node(task, node);
}

void FIFOScheduler::operator()()
{
  _console->info("Started");

  while (true)
  {
    update();
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

void FIFOScheduler::add_node(std::string connstr)
{
  SchedulerNode new_node;
  new_node.connstr = connstr;
  new_node.free = true;

  _node_mutex.lock();
  _free_nodes.push(new_node);
  _node_mutex.unlock();


  _console->info("Node added: " + connstr);
}

void FIFOScheduler::add_task(Task task)
{
  _tasks.push(task);
  _console->debug("New task added: " + std::to_string(task.id));
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
  _node_mutex.lock();
  auto node{_full_nodes[id]};
  _full_nodes.erase(id);
  _free_nodes.push(node);
  _node_mutex.unlock();

  _console->debug("Task done: " + std::to_string(id));
}