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

void start_code_file(const mapreduce::Job *job, const std::string code_localtion, const int num_workers)
{
  const auto console{spdlog::get("console")};

  for (int i = 0; i < num_workers; i++)
  {
    switch (job->ext())
    {
    case 0:
      console->info(job->job_id() + " python worker started");
      exec(("python3 " + code_localtion).c_str());
      break;

    default:
      break;
    }
  }
}

grpc::Status Node::JobStart(grpc::ServerContext *context, const mapreduce::Job *job, mapreduce::Empty *response)
{
  const auto console{spdlog::get("console")};
  console->info("New job " + job->job_id() + " received from " + context->peer());

  const std::string code_location{write_code_file(job)};
  console->info(job->job_id() + " written to disk: " + code_location);

  _workers[job->job_id()] = job->chunks_size();
  _jobs.insert(std::pair<std::string, mapreduce::Job>(job->job_id(), *job));

  start_code_file(job, code_location, job->chunks_size());
  response->Clear();

  return grpc::Status::OK;
}

grpc::Status Node::JobGet(grpc::ServerContext *context, const mapreduce::JobRequest *request, mapreduce::Job *response)
{
  const auto console{spdlog::get("console")};
  console->info(request->job_id() + " request received from " + context->peer());

  mapreduce::Job job{_jobs[request->job_id()]};
  const int last_chunk_index{job.chunks_size() - 1};
  response->set_job_id(job.job_id());
  response->add_chunks(job.chunks(last_chunk_index));
  _jobs[request->job_id()].mutable_chunks()->RemoveLast();

  console->info(request->job_id() + " responded with job to " + context->peer());

  return grpc::Status::OK;
}

grpc::Status Node::JobMapped(grpc::ServerContext *context, const mapreduce::MappedJob *results, mapreduce::Empty *response)
{
  _workers[results->job_id()] -= 1;
  const u_int8_t workers_left{_workers[results->job_id()]};

  const auto console{spdlog::get("console")};
  console->info(results->job_id() + " mapped results received from " + context->peer());
  console->info(results->job_id() + ": " + std::to_string(workers_left) + " workers left");

  for (auto &&pair : results->pairs())
  {
    console->info(pair.key() + " " + std::to_string(pair.value()));
    _mapresults[results->job_id()].push_back(pair);
  }

  if (!workers_left)
  {
    _jobs[results->job_id()].clear_chunks();
    _workers.erase(results->job_id());
    console->info(results->job_id() + ": " + std::to_string(_mapresults[results->job_id()].size()) + " results");
  }

  response->Clear();
  return grpc::Status::OK;
}