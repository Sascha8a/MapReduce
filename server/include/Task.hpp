#pragma once

#include <string>

/**
 * @brief Struct containing information of a task.
 * Contains a unique identifier and some form of protobuf message, that is delivered to nodes.
 * 
 */
struct Task
{
  long id;
  std::string job;
};