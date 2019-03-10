#include <grpcpp/grpcpp.h>
#include <vector>
#include <fmt/format.h>
#include "asio_protobuf_util.hpp"
#include "internal.grpc.pb.h"
#include "internal.pb.h"
#include "CLI11.hpp"
#include "json.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

using namespace nlohmann;

std::string get_file(std::string filename)
{
  spdlog::info(fmt::format("Reading {0}...", filename));
  std::ifstream fstream;
  std::stringstream sstream;

  fstream.open(filename);
  sstream << fstream.rdbuf();
  fstream.close();

  return sstream.str();
}

bool invalid_char(char c)
{
  return !isascii(c);
}

void strip_unicode(std::string &str)
{
  str.erase(remove_if(str.begin(), str.end(), invalid_char), str.end());
}

std::vector<std::string> input_linewise(std::string input_file_uri)
{
  std::vector<std::string> results;
  std::ifstream fstream;
  std::string line;

  try
  {
    fstream.open(input_file_uri);
  }
  catch (const std::exception &e)
  {
    spdlog::error(fmt::format("Error opening input file: {}", e.what()));
    std::exit(0);
  }

  spdlog::info("Reading {}...", input_file_uri);
  while (getline(fstream, line))
  {
    strip_unicode(line);
    results.push_back(line + " \n");
  }

  if (results.size())
  {
    spdlog::info(fmt::format("Got {} lines", results.size()));
  }
  else
  {
    spdlog::error("Found 0 lines. Does the file exist?");
    std::exit(0);
  }

  return results;
}

std::vector<std::string> input_linewise(std::string input_file_uri, int chunk_size = 1)
{
  std::vector<std::string> results;
  std::ifstream fstream;
  std::string line;
  std::string intermediate_result{""};
  int counter{0};

  try
  {
    fstream.open(input_file_uri);
  }
  catch (const std::exception &e)
  {
    spdlog::info(fmt::format("Error opening input file: {}", e.what()));
    std::exit(0);
  }
  spdlog::info(fmt::format("Reading {}...", input_file_uri));
  while (getline(fstream, line))
  {
    strip_unicode(line);
    intermediate_result += (line + " \n");
    counter += 1;

    if (counter == chunk_size)
    {
      results.push_back(intermediate_result);

      intermediate_result = "";
      counter = 0;
    }
  }

  results.push_back(intermediate_result);

  if (results.size())
  {
    spdlog::info(fmt::format("Got {} lines", results.size()));
  }
  else
  {
    spdlog::error("Found 0 lines. Does the file exist?");
    std::exit(0);
  }

  return results;
}

long upload_data(std::vector<std::string> &code, std::vector<std::string> &data, std::string ip, std::string port)
{
  asio::io_context io_context;
  asio::ip::tcp::resolver resolver{io_context};
  asio::ip::tcp::socket socket{io_context};
  auto result{resolver.resolve(ip, port)};

  try
  {
    asio::connect(socket, result);
    spdlog::info("Connected to data upload port");
  }
  catch (const std::exception &e)
  {
    spdlog::error(fmt::format("Error connecting: {}", e.what()));
    std::exit(0);
  }

  spdlog::info("Sending code...");
  for (auto &&code_chunk : code)
  {
    mapreduceAPI::CodeChunk message;
    message.set_code_chunk(code_chunk);

    asio_utils::send_proto_no_type(socket, message);
  }

  spdlog::info("Sending data...");
  for (auto &&data_chunk : data)
  {
    mapreduceAPI::DataChunk message;
    message.set_data_chunk(data_chunk);

    asio_utils::send_proto_no_type(socket, message);
  }

  spdlog::info("Receiving job id...");
  mapreduceAPI::JobStatusResponse response;
  asio_utils::receive_proto_message(socket, response);

  return response.job_id();
}

void create_job(std::vector<std::string> &data, std::vector<std::string> &code, std::string master_ip, std::string master_port)
{
  asio::io_context io_context;
  asio::ip::tcp::resolver resolver{io_context};
  asio::ip::tcp::socket socket{io_context};
  auto result{resolver.resolve(master_ip, master_port)};
  try
  {
    asio::connect(socket, result);
    spdlog::info("Connected with master on {}:{}", master_ip, master_port);
  }
  catch (const std::exception &e)
  {
    spdlog::error("Error connecting to master: {}", e.what());
    return;
  }

  mapreduceAPI::JobCreationRequest request;
  request.set_num_code_chunks(code.size());
  request.set_num_data_chunks(data.size());

  spdlog::debug("Sending JobCreationRequest...");
  asio_utils::send_proto(socket, request);

  asio_utils::MessageType message_type;
  asio_utils::receive_proto_message_type(socket, message_type);

  spdlog::debug("Receiving JobCreationResponse...");
  mapreduceAPI::JobCreationResponse response;
  asio_utils::receive_proto_message(socket, response);
  spdlog::info("Port for data upload: {}", response.port());

  auto job_id{upload_data(code, data, master_ip, std::to_string(response.port()))};
  spdlog::info("Finished creating job - ID: {}", job_id);
  spdlog::info("Use './cli status --id {}' to retrieve results", job_id);
}

void start_job(std::string config_url)
{
  const auto config_string{get_file(config_url)};
  std::vector<std::string> input_chunks;
  std::vector<std::string> code_chunks;

  json config;

  try
  {
    config = json::parse(config_string);
  }
  catch (const std::exception &e)
  {
    spdlog::error("Error parsing config: {}", e.what());
    return;
  }

  if (config["split"] == "line")
  {
    input_chunks = input_linewise(config["input"], 1);
    code_chunks = input_linewise(config["code"], 1);
  }
  else if (config["split"] == "line64")
  {
    input_chunks = input_linewise(config["input"], 1024);
    code_chunks = input_linewise(config["code"], 1024);
  }
  else
  {
    spdlog::error("Unrecognised split option. Possible: 'line'");
    return;
  }

  create_job(input_chunks, code_chunks, config["ip"], config["port"]);
}

void get_status(long job_id, std::string master_ip, std::string master_port)
{
  asio::io_context io_context;
  asio::ip::tcp::resolver resolver{io_context};
  asio::ip::tcp::socket socket{io_context};
  auto result{resolver.resolve(master_ip, master_port)};
  try
  {
    asio::connect(socket, result);
    spdlog::info("Connected with master on {}:{}", master_ip, master_port);
  }
  catch (const std::exception &e)
  {
    spdlog::error("Error connecting to master: {}", e.what());
    return;
  }

  mapreduceAPI::JobStatusRequest request;
  request.set_job_id(job_id);
  spdlog::debug("Sending JobStatusRequest...");
  asio_utils::send_proto(socket, request);

  spdlog::debug("Receiving JobStatusResponse...");
  mapreduceAPI::JobStatusResponse response;
  asio_utils::receive_proto_message(socket, response);

  if (response.status() == mapreduceAPI::JobStatus::init)
  {
    spdlog::info("Status: Job initializing");
  }
  else if (response.status() == mapreduceAPI::JobStatus::map_phase)
  {
    spdlog::info("Status: Job in map phase");
    spdlog::info("Progress: {}/{} jobs left", response.map_tasks_remaining(), response.map_tasks());
  }
  else if (response.status() == mapreduceAPI::JobStatus::reduce_phase)
  {
    spdlog::info("Status: Job in reduce phase");
    spdlog::info("Progress: {}/{} jobs left", response.reduce_tasks_remaining(), response.reduce_tasks());
  }
  else if (response.status() == mapreduceAPI::JobStatus::notfound)
  {
    spdlog::error("Job not found");
  }
  else
  {
    spdlog::info("Status: Job finished");
    json results_array{json::array()};

    for (auto &&pair : response.results())
    {
      results_array.push_back({pair.key(), pair.value()});
    }

    std::ofstream results_file_stream;
    results_file_stream.open("results.txt");
    results_file_stream << results_array;
    results_file_stream.close();

    spdlog::info("Results written to results.txt");
  }
}

int main(int argc, char *argv[])
{
  spdlog::stderr_color_mt("MapReduce CLI");
  CLI::App map_reduce_cli{"CLI for the mapreduce project", "CLI"};
  map_reduce_cli.require_subcommand(1);

  CLI::App *start = map_reduce_cli.add_subcommand("start", "Start a new job");
  std::string config_url;
  start->add_option("-c,--config", config_url, "Location of the config file")->required()->check(CLI::ExistingFile);

  CLI::App *status = map_reduce_cli.add_subcommand("status", "Status of a job");
  long job_id;
  status->add_option("--id", job_id, "Job ID")->required();
  std::string master_ip{"127.0.0.1"};
  status->add_option("--ip", master_ip, "Job ID");
  std::string master_port{"3000"};
  status->add_option("--p", master_port, "Job ID");

  CLI11_PARSE(map_reduce_cli, argc, argv);

  if (map_reduce_cli.got_subcommand(start))
  {
    start_job(config_url);
  }
  else if (map_reduce_cli.got_subcommand(status))
  {
    get_status(job_id, master_ip, master_port);
  }
  else
  {
    spdlog::error("No command given");
  }

  return 0;
}
