#include <grpcpp/grpcpp.h>
#include <iostream>
#include <fstream>

#include "spdlog/spdlog.h"
#include "internal.grpc.pb.h"
#include "internal.pb.h"

#include "Node.hpp"

std::string get_extension_from_type(mapreduce::CodeExt ext)
{
  switch (ext)
  {
  case 0:
    return ".py";
    break;

  case 1:
    return "";
    break;

  default:
    return "";
    break;
  }
}

std::string write_code_file(const mapreduce::Job *job)
{
  const std::string filename{"/tmp/" + job->job_id() + get_extension_from_type(job->ext())};
  std::ofstream stream;

  stream.open(filename); // TODO: Configurable folder to save files.
  stream << job->code();
  stream.close();

  return filename;
}

void exec(const char *cmd)
{
  std::string result;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
  if (!pipe)
  {
    throw std::runtime_error("popen() failed!");
  }
}

void start_code_file(const mapreduce::Job *job, const std::string code_localtion)
{
  switch (job->ext())
  {
  case 0:
    exec(("python3 " + code_localtion).c_str());
    break;

  default:
    break;
  }
}

grpc::Status Node::StartJob(grpc::ServerContext *context, const mapreduce::Job *job, mapreduce::Empty *response)
{
  const auto console{spdlog::get("console")};
  console->info(job->job_id() + " received from " + context->peer());

  const std::string code_location{write_code_file(job)};
  console->info(job->job_id() + " written to disk: " + code_location);

  start_code_file(job, code_location);
  console->info(job->job_id() + " started");

  _jobs.insert(std::pair<std::string, mapreduce::Job>(job->job_id(), *job));
  response->Clear();

  return grpc::Status::OK;
}

grpc::Status Node::GetJob(grpc::ServerContext *context, const mapreduce::JobRequest *request, mapreduce::Job *response)
{
  const auto console{spdlog::get("console")};
  console->info(request->job_id() + " request received from " + context->peer());

  mapreduce::Job job = _jobs.at(request->job_id());
  response->set_job_id(job.job_id());

  console->info(request->job_id() + " responded with job to " + context->peer());

  return grpc::Status::OK;
}

grpc::Status Node::MappedJob(grpc::ServerContext *context, const mapreduce::MapResults *results, mapreduce::Empty *response)
{
  const auto console{spdlog::get("console")};
  console->info(request->job_id() + " mapped results received from " + context->peer());

  _jobs[request->job_id()].clear_chunk();

  return grpc::Status::OK;
}