#include <asio.hpp>
#include <vector>

#include "APIServer.hpp"
#include "asio_protobuf_util.hpp"

APIServer::APIServer(short unsigned int port, Master *master)
{
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

  while (true)
  {
    tcp::socket socket{acceptor.accept()};
    asio_utils::MessageType message_type;
    asio_utils::receive_proto_message_type(socket, message_type);

    if (message_type == asio_utils::MessageType::JobCreationRequest)
    {
      mapreduceAPI::JobCreationRequest request;
      asio_utils::receive_proto_message(socket, request);
    }
    else
    {
      _console->error("Received unrecognised message");
    }
  }
}

void APIServer::start_data_receiver(short unsigned int port, long num_code_chunks, long num_data_chunks)
{
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

  socket.close();
}