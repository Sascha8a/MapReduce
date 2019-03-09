#pragma once

#include <string>
#include <map>

/**
 * @brief Struct that contains information about a particular node.
 * It consits of a connection string, and wether or not it's currently free for connections.
 * 
 */
struct SchedulerNode
{
  std::string connstr;
  bool free;
};