#pragma once

#include <grpcpp/grpcpp.h>

#include "internal.grpc.pb.h"
#include "internal.pb.h"

class Master final : public mapreduce::Master::Service
{
public:
  Master();
};
