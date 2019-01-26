#include <iostream>

#include "Master.hpp"
#include "spdlog/spdlog.h"

Master::Master(/* args */)
{
}

Master::~Master()
{
}

void Master::start()
{
  spdlog::info("Master is starting...");
}