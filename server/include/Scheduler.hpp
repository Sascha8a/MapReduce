#pragma once

#include <string>
#include <map>

#include "Task.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

struct SchedulerNode
{
  std::string connstr;
  bool free;
};

class Scheduler
{
protected:
  std::shared_ptr<spdlog::logger> _console{spdlog::stderr_color_mt("Scheduler")};
  void send_to_node(Task, SchedulerNode);
  Scheduler(){};

public:
  virtual ~Scheduler(){};
  virtual void add_node(std::string);
  virtual void add_task(Task);
  virtual void task_done(Task);
};