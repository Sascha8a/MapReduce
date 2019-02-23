#pragma once

#include <queue>
#include <map>
#include <thread>
#include <mutex>

#include "Task.hpp"
#include "Scheduler.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

class FIFOScheduler
{
private:
  std::queue<Task> _tasks;
  std::thread _loop_thread;
  std::queue<SchedulerNode> _free_nodes;
  std::map<long, SchedulerNode> _full_nodes;
  std::mutex _node_mutex;
  std::shared_ptr<spdlog::logger> _console{spdlog::stderr_color_mt("FIFOScheduler")};
  void update();
  void send_to_node(Task, SchedulerNode);

public:
  FIFOScheduler();
  // ~FIFOScheduler() {};
  void operator()();
  void add_node(std::string);
  void add_task(Task);
  void task_done(Task);
};