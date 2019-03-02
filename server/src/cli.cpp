#include <grpcpp/grpcpp.h>
#include <vector>

#include "asio_protobuf_util.hpp"
#include "internal.grpc.pb.h"
#include "internal.pb.h"
#include "CLI11.hpp"

std::string get_file(std::string filename)
{
  std::ifstream fstream;
  std::stringstream sstream;

  fstream.open(filename);
  sstream << fstream.rdbuf();

  return sstream.str();
}

long upload_data(std::string ip, std::string port, std::vector<std::string> *code, std::vector<std::string> *data)
{
  asio::io_context io_context;
  asio::ip::tcp::resolver resolver{io_context};
  asio::ip::tcp::socket socket{io_context};
  auto result{resolver.resolve(ip, port)};
  asio::connect(socket, result);

  for (auto &&code_chunk : *code)
  {
    mapreduceAPI::CodeChunk message;
    message.set_code_chunk(code_chunk);

    asio_utils::send_proto_no_type(socket, message);
  }

  for (auto &&data_chunk : *data)
  {
    mapreduceAPI::DataChunk message;
    message.set_data_chunk(data_chunk);

    asio_utils::send_proto_no_type(socket, message);
  }

  mapreduceAPI::JobStatusResponse response;
  asio_utils::receive_proto_message(socket, response);

  return response.job_id();
}

void fn_master_start()
{
}

void fn_master_stop()
{
}

void fn_master_test()
{
  // auto channel{grpc::CreateChannel("localhost:50050", grpc::InsecureChannelCredentials())};
  // auto stub = mapreduce::Master::NewStub(channel);

  // mapreduce::NewJob job;

  // const string code{get_file("impl.py")};
  // job.set_code(code);
  // const string data{get_file("shakespeare.txt")};
  // job.set_data(data);

  // grpc::ClientContext context;
  // mapreduce::Empty response;
  // grpc::Status status{stub->JobStart(&context, job, &response)};

  // if (status.ok())
  // {
  //   // cout << "Job sent" << endl;
  // }
  // else
  // {
  //   // cout << status.error_message() << endl;
  // }
}

void fn_master_cli_test()
{
  std::vector<std::string> data;
  std::vector<std::string> code;
  code.push_back(get_file("impl.py")); //TODO: Config
  data.push_back("a a a");
  data.push_back("b b");
  data.push_back("c");
  // std::string input{get_file("shakespeare.txt")};

  // size_t pos = 0;
  // std::string token;
  // std::string seperator{"\n"};
  // while ((pos = input.find(seperator)) != std::string::npos)
  // {
  //   token = input.substr(0, pos);
  //   data.push_back(token);
  //   input.erase(0, pos + seperator.length());
  // }

  asio::io_context io_context;
  asio::ip::tcp::resolver resolver{io_context};
  asio::ip::tcp::socket socket{io_context};
  auto result{resolver.resolve("127.0.0.1", "3000")};
  asio::connect(socket, result);

  mapreduceAPI::JobCreationRequest request;
  request.set_num_code_chunks(code.size());
  request.set_num_data_chunks(data.size());

  asio_utils::send_proto(socket, request);

  asio_utils::MessageType message_type;
  asio_utils::receive_proto_message_type(socket, message_type);

  mapreduceAPI::JobCreationResponse response;
  asio_utils::receive_proto_message(socket, response);

  upload_data("127.0.0.1", std::to_string(response.port()), &code, &data); //TODO: Config
}

void fn_master_logs_stream()
{
}

void fn_todo()
{
}

int main(int argc, char *argv[])
{
  CLI::App map_reduce_cli{"CLI for the mapreduce project", "CLI"};
  map_reduce_cli.failure_message(CLI::FailureMessage::help);
  map_reduce_cli.require_subcommand(1);

  // CLI Master section
  CLI::App *master_cli = map_reduce_cli.add_subcommand("master", "Manage the master instance");
  master_cli->require_subcommand(1);
  CLI::App *master_start = master_cli->add_subcommand("start", "Start a new instance");
  master_start->callback(*fn_master_start);
  CLI::App *master_stop = master_cli->add_subcommand("stop", "Stop the instance");
  master_stop->callback(*fn_master_stop);
  CLI::App *master_test = master_cli->add_subcommand("test", "Tests master instance functionality with a simple test");
  master_test->callback(*fn_master_test);

  CLI::App *master_cli_test = master_cli->add_subcommand("testapi", "Tests ApiServer instance functionality with a simple test");
  master_cli_test->callback(*fn_master_cli_test);

  CLI::App *master_logs = master_cli->add_subcommand("logs", "Stream the log");
  master_logs->callback(*fn_master_logs_stream);
  // CLI::App *jobs_cli = map_reduce_cli.add_subcommand("jobs", "A set of commands for monitoring jobs.");
  // CLI::App *jobs_cli = map_reduce_cli.add_subcommand("node", "A set of commands for node management.");

  CLI11_PARSE(map_reduce_cli, argc, argv);
  return 0;
}
