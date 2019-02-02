#include <iostream>
#include <sstream>
#include <fstream>
#include <thread>
#include <grpcpp/grpcpp.h>
#include <iostream>

#include "internal.grpc.pb.h"
#include "internal.pb.h"
#include "Node.hpp"

std::string get_file()
{
  std::ifstream fstream;
  std::stringstream sstream;

  fstream.open("code.py");
  sstream << fstream.rdbuf();

  return sstream.str();
}

int main()
{
  auto channel{grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials())};
  auto stub = mapreduce::Node::NewStub(channel);

  grpc::ClientContext context;
  mapreduce::Job job;

  const std::string code{get_file()};

  job.set_job_id("aaa");
  job.set_code(code);
  job.add_chunks("a a b b c c"); // a:2 b:2 c:2
  job.add_chunks("a b c");       // a:1 b:1 c:1
  job.add_chunks("a");           // a:1
                                // a:4 b:3 c:3

  mapreduce::Empty response;
  grpc::Status status = stub->StartJob(&context, job, &response);

  if (status.ok())
  {
    std::cout << "Success" << std::endl;
  }
  else
  {
    std::cout << "ERROR" << std::endl;
  }

  return 0;
}
