#include <asio.hpp>
#include <vector>

#include "APIServer.hpp"
#include "asio_protobuf_util.hpp"

#define MIN_PORT 3001
#define MAX_PORT 3200
static gpr_atm s_pick_counter = 0;

/**
 * Source: https://github.com/grpc/grpc/blob/ea232d16d37b8e88806fca3843a360cc338d1a17/test/core/util/port_isolated_runtime_environment.cc#L36-L41
 **/
static int get_random_port_offset()
{
  srand(gpr_now(GPR_CLOCK_REALTIME).tv_nsec);
  double rnd = static_cast<double>(rand()) /
               (static_cast<double>(RAND_MAX) + 1.0); // values from [0,1)
  return static_cast<int>(rnd * (MAX_PORT - MIN_PORT + 1));
}

int grpc_pick_unused_port(void)
{
  int orig_counter_val =
      static_cast<int>(gpr_atm_full_fetch_add(&s_pick_counter, 1));
  GPR_ASSERT(orig_counter_val < (MAX_PORT - MIN_PORT + 1));
  return MIN_PORT +
         (get_random_port_offset() + orig_counter_val) % (MAX_PORT - MIN_PORT + 1);
}

APIServer::APIServer(int port, Master *master, bool debug)
{
  if (debug)
  {
    _console->set_level(spdlog::level::debug);
  }

  _master = master;
  _thread = std::thread(&APIServer::start_server, this, port);
  _thread.detach();
}

void APIServer::start_server(short unsigned int port)
{
  asio::io_context io_context;
  asio::ip::tcp::endpoint endpoint{asio::ip::tcp::v4(), port};
  asio::ip::tcp::acceptor acceptor{io_context, endpoint};

  acceptor.listen();
  _console->info("Started");

  while (true)
  {
    tcp::socket socket{acceptor.accept()};
    asio_utils::MessageType message_type;
    asio_utils::receive_proto_message_type(socket, message_type);

    if (message_type == asio_utils::MessageType::JobCreationRequest)
    {
      mapreduceAPI::JobCreationRequest request;
      asio_utils::receive_proto_message(socket, request);
      _console->debug("Received JobCreationRequest");

      const int port{grpc_pick_unused_port()};

      std::thread thread{&APIServer::start_data_receiver, this, port, request.num_code_chunks(), request.num_data_chunks()};
      thread.detach();
      std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //TODO: Synchronize threads

      mapreduceAPI::JobCreationResponse response;
      response.set_port(port);
      asio_utils::send_proto(socket, response);

      socket.close();
    }
    else if (message_type == asio_utils::MessageType::JobStatusRequest)
    {
      mapreduceAPI::JobStatusRequest request;
      asio_utils::receive_proto_message(socket, request);
      _console->debug("Received JobStatusRequest");

      const long job_id{request.job_id()};

      mapreduceAPI::JobStatusResponse response{_master->get_status(job_id)};
      response.set_job_id(job_id);

      if (response.status() == mapreduceAPI::JobStatus::finished)
      {
        for (auto &&result : _master->get_results(job_id))
        {
          auto pair{response.add_results()};
          pair->set_key(result.first);
          pair->set_value(result.second);
        }

        _master->clear_results(job_id);
      }

      asio_utils::send_proto_no_type(socket, response);
      socket.close();
    }
    else
    {
      _console->error("Received unrecognised message!");
    }
  }
}

void APIServer::start_data_receiver(short unsigned int port, long num_code_chunks, long num_data_chunks)
{
  _console->debug("Waiting for job creation data on port {}", std::to_string(port));

  asio::io_context io_context;
  asio::ip::tcp::endpoint endpoint{asio::ip::tcp::v4(), port};
  asio::ip::tcp::acceptor acceptor{io_context, endpoint};
  acceptor.listen();
  tcp::socket socket{acceptor.accept()};

  std::string code{""};
  std::vector<std::string> chunks;

  for (int i = 0; i < num_code_chunks; i++)
  {
    mapreduceAPI::CodeChunk message;
    asio_utils::receive_proto_message(socket, message);
    code += message.code_chunk();
  }

  for (int i = 0; i < num_data_chunks; i++)
  {
    mapreduceAPI::DataChunk message;
    asio_utils::receive_proto_message(socket, message);
    chunks.push_back(message.data_chunk());
  }

  long id{_master->StartJob(chunks, code)};

  mapreduceAPI::JobStatusResponse response;
  response.set_status(mapreduceAPI::JobStatus::init);
  response.set_job_id(id);

  asio_utils::send_proto_no_type(socket, response);

  socket.close();
}