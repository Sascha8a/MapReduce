#pragma once

#include <asio.hpp>
#include <thread>

#include "Master.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

/**
 * @brief This class provides an API endpoint for external software (such as the CLI) to control MapReduce.
 */
class APIServer
{
private:
  Master *_master;
  std::thread _thread;
  std::shared_ptr<spdlog::logger> _console{spdlog::stderr_color_mt("APIServer")};

  /**
   * @brief Internal method, that is started in a thread and exposes the API via a TCP port.
   * 
   * @param port Port for the api endpoint
   */
  void start_server(short unsigned int port);

  /**
   * @brief Internal method, to be started in a thread, that receives data from jobs and sends them to the master
   * 
   * @param port Port for data upload
   * @param num_code_chunks Number of code chunks to expect (See documentation)
   * @param num_data_chunks Number of data chunks to expect (See documentation)
   */
  void start_data_receiver(short unsigned int port, long num_code_chunks, long num_data_chunks);

public:
  APIServer(int port, Master *master, bool debug);
  ~APIServer(){};
};