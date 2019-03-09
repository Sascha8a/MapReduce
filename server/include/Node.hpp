#pragma once

#include <grpcpp/grpcpp.h>
#include <map>
#include <vector>

#include "internal.grpc.pb.h"
#include "internal.pb.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

/**
 * @brief The node is the "worker" part of the MapReduce cluster.
 * It executes code on the dataset and sends the result to the master.
 * 
 */
class Node final : public mapreduce::Node::Service
{
private:
  std::string _chunk;
  std::string _reduce_key;
  std::vector<int> _reduce_values;
  long _task_id;
  long _job_id;
  std::string _master_uri;
  std::string _own_uri;
  std::shared_ptr<spdlog::logger> _console{spdlog::stderr_color_mt("Node")};
  std::mutex _node_mutex;

public:
  Node(std::string node_uri, bool debug)
  {
    _own_uri = node_uri;
    if (debug)
    {
      _console->set_level(spdlog::level::debug);
    }
  }

  /**
   * @brief Called by the worker (see documentation).
   * This method returns the current job (and data) to the worker for processing
   * 
   */
  grpc::Status JobGet(grpc::ServerContext *context, const mapreduce::Empty *request, mapreduce::Job *response) override;
 
   /**
   * @brief Called by the worker (see documentation). To send results.
   * 
   */
  grpc::Status JobMapped(grpc::ServerContext *context, const mapreduce::MappedJob *job, mapreduce::Empty *response) override;
 
  /**
   * @brief Called by the worker (see documentation). To send results.
   * 
   */
  grpc::Status JobReduced(grpc::ServerContext *context, const mapreduce::ReducedJob *job, mapreduce::Empty *response) override;
  
  /**
   * @brief Called by the master (see documentation).
   * This is used to send data to the node and start a worker for processing
   * 
   */
  grpc::Status StartTask(grpc::ServerContext *context, const mapreduce::Task *task, mapreduce::Empty *response) override;
  
  /**
   * @brief Helfer function to write code to a file
   * 
   * @param id Unique identifier for the file (Job id)
   * @param ext File extension (py, ...)
   * @param code String with the code
   * @return std::string Returns the path to the file
   */
  std::string write_code_file(const long id, const mapreduce::CodeExt ext, const std::string code);

  /**
   * @brief Helper function to execute source code.
   * 
   * @param ext File extension (.py, ...)
   * @param code_localtion File path)
   */
  void start_code_file(const mapreduce::CodeExt ext, const std::string code_localtion);

  /**
   * @brief Call this function, when you are ready to receive tasks
   * 
   * @param uri Connection string of the master server
   */
  void register_at_master(std::string uri);

  /**
   * @brief Helper function to clean the node's memory
   * 
   */
  void clean();
};
