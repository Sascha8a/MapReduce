#include <iostream>
#include <thread>

#include <grpcpp/grpcpp.h>

#include "Master.cpp"
#include "helloworld.grpc.pb.h"
#include "helloworld.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

class GreeterServiceImpl final : public Greeter::Service
{
  Status SayHello(ServerContext *context, const HelloRequest *request,
                  HelloReply *reply) override
  {
    if (!context) {
      return Status::CANCELLED;
    }
    std::string prefix("Hello ");
    reply->set_message(prefix + request->name());
    return Status::OK;
  }
};

//int main(int argc, char* argv[]) {
int main()
{
  GreeterServiceImpl service;
  ServerBuilder builder;
  builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  server->Wait();

  Master m{};
  m.start();

  return 0;
}
