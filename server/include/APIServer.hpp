#pragma once

#include <thread>

#include "Master.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

class APIServer
{
private:
  Master *_master;
  std::thread _thread;
  std::shared_ptr<spdlog::logger> _console{spdlog::stderr_color_mt("APIServer")};
  void start_server(short unsigned int port);
  void start_data_receiver(short unsigned int port, long num_code_chunks, long num_data_chunks);

public:
  APIServer(short unsigned int port, Master *master);
  ~APIServer(){};
};