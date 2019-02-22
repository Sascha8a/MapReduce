#pragma once

#include <queue>
#include <map>
#include <thread>
#include <mutex>

#include "Scheduler.hpp"

class FIFOScheduler : public Scheduler
{
private:
  std::queue<Task> _tasks;
  std::thread _loop_thread;
  std::queue<SchedulerNode> _free_nodes;
  std::map<long, SchedulerNode> _full_nodes;
  std::mutex _node_mutex;
  void update();

public:
  FIFOScheduler();
  ~FIFOScheduler();
  void operator()();
  void add_node(std::string);
  void add_task(Task);
  void task_done(Task);
};