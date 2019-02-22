#include "FIFOScheduler.hpp"

#include <iostream>
#include <thread>
#include <chrono>

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