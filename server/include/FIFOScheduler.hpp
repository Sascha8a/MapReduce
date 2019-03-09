#pragma once

#include <queue>
#include <map>
#include <thread>
#include <mutex>

#include "Task.hpp"
#include "Scheduler.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

/**
 * @brief The purpose of this clas is simple: Schedule and send "tasks" to nodes.
 * This node doesn't care about the current phase of a job etc. It just schedules
 * Do not forget, to call the operator()() in a new thread to process the tasks as needed.
 * 
 */
class FIFOScheduler
{
private:
  std::queue<Task> _tasks;
  long _new_task_id{0};
  std::thread _loop_thread;
  std::queue<SchedulerNode> _free_nodes;
  std::map<long, SchedulerNode> _full_nodes;
  std::mutex _node_mutex;
  std::shared_ptr<spdlog::logger> _console{spdlog::stderr_color_mt("FIFOScheduler")};

  /**
   * @brief Internal method, runs one cycle of the scheduler loop
   * 
   */
  void update();

  /**
   * @brief Helper function to send tasks to nodes.
   * 
   * @param task Task to be sent
   * @param node Node to send it to
   */
  void send_to_node(Task task, SchedulerNode node);

  /**
   * @brief Adds a new task to the scheduler for scheduling
   * 
   * @param task Task to be executed
   */
  void add_task(Task task);

public:
  FIFOScheduler(bool debug);
  ~FIFOScheduler(){};

  /**
   * @brief Start me in a thread to actually process tasks
   * 
   */
  void operator()();

  /**
   * @brief Add a new node for scheduling
   * 
   * @param node Connection string of the node
   */
  void add_node(std::string node);

  /**
   * @brief Add a new task for scheduling
   * 
   * @param protobuf_msg Job encoded as a protobuf message. The scheduler doesn't care about the content
   */
  void add_task(std::string protobuf_msg);

  /**
   * @brief Call this method once a task has been reported done
   * 
   * @param id id of the task
   */
  void task_done(long id);
};