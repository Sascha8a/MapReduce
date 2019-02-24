#include <sstream>
#include <thread>

#include "Master.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "internal.grpc.pb.h"
#include "internal.pb.h"

Master::Master()
{
  _console->set_level(spdlog::level::debug); //TODO: Config

  std::thread sch_thread{std::ref(_scheduler)};
  sch_thread.detach();
}

std::vector<std::string> chunk_data(std::string data)
{
  std::stringstream ss(data);
  std::string item;
  std::vector<std::string> lines;

  while (std::getline(ss, item))
  {
    lines.push_back(item);
  }

  return lines;
}

grpc::Status Master::RegisterNode(grpc::ServerContext *context, const mapreduce::NewNode *node, mapreduce::Empty *response)
{
  _console->info("New connection fron Node " + context->peer());

  _scheduler.add_node(node->connstr());

  response->Clear();
  return grpc::Status::OK;
}

grpc::Status Master::JobStart(grpc::ServerContext *context, const mapreduce::NewJob *job, mapreduce::Empty *response)
{
  _console->info("New job from " + context->peer());
  _console->debug("Job data\n" + job->data());
  _console->debug("Job data end");
  _console->debug("Job code\n" + job->code());
  _console->debug("Job code end");
  std::vector<std::string> chunks{chunk_data(job->data())};

  _job_trackers.insert({1, JobTracker(1, &_scheduler, chunks, job->code())});
  response->Clear();
  return grpc::Status::OK;
}

grpc::Status Master::TaskDone(grpc::ServerContext *context, const mapreduce::Task *task, mapreduce::Empty *response)
{
  mapreduce::ReducedJob r_job;
  if (r_job.ParseFromString(task->job()) && r_job.result())
  {
    _scheduler.task_done(task->id());
    _job_trackers.at(r_job.id()).reduced(r_job);

    _console->debug("Reduce job done");
    return grpc::Status::OK;
  }

  mapreduce::MappedJob m_job;
  if (m_job.ParseFromString(task->job()))
  {
    _scheduler.task_done(task->id());
    _job_trackers.at(m_job.id()).mapped(m_job);

    _console->debug("Mapping job done");
    return grpc::Status::OK;
  }

  _console->error("Couldn't parse job in TaskDone");
  context->peer();
  response->SerializeAsString();
  return grpc::Status::CANCELLED;
}