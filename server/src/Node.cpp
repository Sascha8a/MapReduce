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
  const std::string filename{"/tmp/" + std::to_string(id) + get_extension_from_type(ext)};
  std::ofstream stream;

  stream.open(filename); // TODO: Configurable folder to save files.
  stream << code;
  stream.close();

  _console->debug("Code written to " + filename);

  return filename;
}

void exec(const char *cmd) //TODO: Function to method
{
  std::string result;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
  if (!pipe)
  {
    throw std::runtime_error("popen() failed!");
  }
}

void Node::start_code_file(const mapreduce::CodeExt ext, const std::string code_localtion) //TODO: Function to method
{
  std::string cmd = code_localtion + " " + _own_uri;

  switch (ext)
  {
  case 0:
    exec(("python3 " + cmd).c_str());
    break;

  default:
    _console->debug("Extension not recognised");
    break;
  }
}

grpc::Status Node::JobGet(grpc::ServerContext *context, const mapreduce::Empty *request, mapreduce::Job *response)
{
  _console->debug("Worker requesting job: " + context->peer());
  response->set_chunk(_chunk);
  response->set_id(_job_id);
  _console->debug("Job sent");

  request->CheckInitialized();
  return grpc::Status::OK;
}

grpc::Status Node::StartTask(grpc::ServerContext *context, const mapreduce::Task *task, mapreduce::Empty *response)
{
  _task_id = task->id();
  mapreduce::MapJob m_job;

  if (m_job.ParseFromString(task->job()))
  {
    _job_id = m_job.job_id();
    _console->info("Map job received from: " + context->peer());

    const std::string code_location{write_code_file(m_job.job_id(), m_job.ext(), m_job.code())};
    _chunk = m_job.chunk();
    start_code_file(m_job.ext(), code_location);

    response->Clear();
    return grpc::Status::OK;
  }

  return grpc::Status::CANCELLED;
}

grpc::Status Node::JobMapped(grpc::ServerContext *context, const mapreduce::MappedJob *job, mapreduce::Empty *response)
{
  _console->debug("Sending mapped job to master");

  auto channel{grpc::CreateChannel(_master_uri, grpc::InsecureChannelCredentials())};
  auto stub{mapreduce::Master::NewStub(channel)};

  grpc::ClientContext master_context;
  mapreduce::Empty master_response;
  mapreduce::Task msg;
  msg.set_id(_task_id);
  msg.set_job(job->SerializeAsString());

  grpc::Status status{stub->TaskDone(&master_context, msg, &master_response)};

  if (status.ok())
  {
    _console->info("Sent mapped job to master");

    context->peer();
    response->SerializeAsString();
    return grpc::Status::OK;
  }
  else
  {
    _console->error("Error sending mapped job to master: " + status.error_message());
    return grpc::Status::CANCELLED;
  }
}

void Node::register_at_master(std::string master_uri)
{
  _console->debug("Registering at master");
  _master_uri = master_uri;

  auto channel{grpc::CreateChannel(_master_uri, grpc::InsecureChannelCredentials())};
  auto stub{mapreduce::Master::NewStub(channel)};

  grpc::ClientContext context;
  mapreduce::Empty response;
  mapreduce::NewNode msg;
  msg.set_connstr("127.0.0.1:50051"); //TODO: Proper URL

  grpc::Status status{stub->RegisterNode(&context, msg, &response)};

  if (status.ok())
  {
    _console->info("Registered with master");
  }
  else
  {
    _console->error("Error registering with master: " + status.error_message());
  }
}
