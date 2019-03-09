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

std::string Node::write_code_file(const long id, const mapreduce::CodeExt ext, const std::string code)
{
  std::to_string(id);
  const std::string filename{"tmp/" + _own_uri + get_extension_from_type(ext)};
  std::ofstream stream;

  stream.open(filename);
  stream << code;
  stream.close();

  _console->debug("Code written to " + filename);

  return filename;
}

void exec(const char *cmd)
{
  system(cmd);
}

void Node::start_code_file(const mapreduce::CodeExt ext, const std::string code_localtion)
{
  _console->debug("Starting " + code_localtion);

  std::string cmd = code_localtion + " " + _own_uri;

  switch (ext)
  {
  case 0:
    exec(("python3 " + cmd + " &").c_str());
    break;

  default:
    _console->debug("Extension not recognised");
    break;
  }

  _console->debug("Done");
}

grpc::Status Node::JobGet(grpc::ServerContext *context, const mapreduce::Empty *request, mapreduce::Job *response)
{
  _console->debug("Worker " + context->peer() + " requesting job. Waiting...");
  std::lock_guard<std::mutex> lock(_node_mutex);

  _console->debug("Done waiting");
  response->set_chunk(_chunk);
  response->set_key(_reduce_key);
  _console->debug("Set _reduce_key: " + _reduce_key);
  response->set_id(_job_id);
  _console->debug("Set _job_id: " + std::to_string(_job_id));

  for (int const &value : _reduce_values)
  {
    response->add_value(value);
  // _console->debug("Added reduce value: " + std::to_string(value));
  }

  std::string empty;
  request->SerializeToString(&empty);

  _console->debug("Sent job to worker");
  return grpc::Status::OK;
}

grpc::Status Node::StartTask(grpc::ServerContext *context, const mapreduce::Task *task, mapreduce::Empty *response)
{
  _console->info("Reduce job received from: " + context->peer() + " Waiting....");
  std::lock_guard<std::mutex> lock(_node_mutex);

  _task_id = task->id();

  mapreduce::ReduceJob r_job;
  if (r_job.ParseFromString(task->job()) && r_job.value_size())
  {
    _console->info("Reduce job received from: " + context->peer());
    _job_id = r_job.job_id();
    _reduce_key = r_job.key();

    for (int const &value : r_job.value())
    {
      _reduce_values.push_back(value);
    }

    const std::string code_location{write_code_file(r_job.job_id(), r_job.ext(), r_job.code())};
    start_code_file(r_job.ext(), code_location);

    _console->debug("Started worker");

    return grpc::Status::OK;
  }

  mapreduce::MapJob m_job;
  if (m_job.ParseFromString(task->job()))
  {
    _console->info("Map job received from: " + context->peer());
    _job_id = m_job.job_id();
    _chunk = m_job.chunk();

    const std::string code_location{write_code_file(m_job.job_id(), m_job.ext(), m_job.code())};
    start_code_file(m_job.ext(), code_location);

    _console->debug("Started worker");

    return grpc::Status::OK;
  }

  _console->error("Couldn't parse job");
  response->Clear();
  return grpc::Status::CANCELLED;
}

grpc::Status Node::JobMapped(grpc::ServerContext *context, const mapreduce::MappedJob *job, mapreduce::Empty *response)
{
  _console->debug("Received mapped job from worker. Waiting....");
  std::lock_guard<std::mutex> lock(_node_mutex);

  _console->debug("Sending mapped job to master");

  auto channel{grpc::CreateChannel(_master_uri, grpc::InsecureChannelCredentials())};
  auto stub{mapreduce::Master::NewStub(channel)};

  grpc::ClientContext master_context;
  mapreduce::Empty master_response;
  mapreduce::Task msg;
  msg.set_id(_task_id);
  msg.set_job(job->SerializeAsString());

  clean();

  grpc::Status status{stub->TaskDone(&master_context, msg, &master_response)};
  _console->info("Sent mapped job to master");

  context->peer();
  response->SerializeAsString();

  return grpc::Status::OK;
}

grpc::Status Node::JobReduced(grpc::ServerContext *context, const mapreduce::ReducedJob *job, mapreduce::Empty *response)
{
  _console->debug("Received reduced job from worker. Waiting....");
  std::lock_guard<std::mutex> lock(_node_mutex);

  _console->debug("Sending reduced job to master");

  auto channel{grpc::CreateChannel(_master_uri, grpc::InsecureChannelCredentials())};
  auto stub{mapreduce::Master::NewStub(channel)};

  grpc::ClientContext master_context;
  mapreduce::Empty master_response;
  mapreduce::Task msg;
  msg.set_id(_task_id);
  msg.set_job(job->SerializeAsString());

  clean();

  grpc::Status status{stub->TaskDone(&master_context, msg, &master_response)};
  _console->info("Sent reduced job to master");

  context->peer();
  response->SerializeAsString();

  return grpc::Status::OK;
}

void Node::register_at_master(std::string master_uri)
{
  std::lock_guard<std::mutex> lock(_node_mutex);

  _console->debug("Registering at master");
  _master_uri = master_uri;

  auto channel{grpc::CreateChannel(_master_uri, grpc::InsecureChannelCredentials())};
  auto stub{mapreduce::Master::NewStub(channel)};

  grpc::ClientContext context;
  mapreduce::Empty response;
  mapreduce::NewNode msg;
  msg.set_connstr(_own_uri);

  grpc::Status status{stub->RegisterNode(&context, msg, &response)};

  if (status.ok())
  {
    _console->info("Registered with master");
  }
  else
  {
    _console->error("Error registering with master: " + status.error_message());
    throw std::runtime_error("Connection to master failed");
  }
}

void Node::clean()
{
  _chunk = "";
  _reduce_key = "";
  _reduce_values.clear();
  _reduce_values.shrink_to_fit();
}