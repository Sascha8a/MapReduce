/**
 * Fork of DiSy by Konstantin Lampalzer
 * URL: https://github.com/Kola50011/DiSy/blob/master/DiSy/src/server/server.cpp
**/

#pragma once

#include <google/protobuf/message.h>
#include <asio.hpp>
#include <unordered_map>
#include <typeindex>

#include "API.grpc.pb.h"
#include "API.pb.h"

using namespace asio::ip;
using asio::buffer;
using asio::streambuf;
using asio::write;
using asio::ip::tcp;

using std::istream;
using std::ostream;

template <typename E>
constexpr auto to_underlying(E e) noexcept
{
  return static_cast<u_int8_t>(static_cast<std::underlying_type_t<E>>(e));
}

namespace asio_utils
{
const int SEND_OK{0};
const int SEND_ERR{1};

enum class MessageType
{
  JobCreationRequest = 1,
  JobCreationResponse = 2,
  CodeChunk = 3,
  DataChunk = 4,
  JobStatusRequest = 5,
  JobStatusResponse = 6,
  JobDeletionApproval = 7
};

const std::unordered_map<std::type_index, MessageType> type_mapping{
    {typeid(mapreduceAPI::JobCreationRequest), MessageType::JobCreationRequest},
    {typeid(mapreduceAPI::JobCreationResponse), MessageType::JobCreationResponse},
    {typeid(mapreduceAPI::CodeChunk), MessageType::CodeChunk},
    {typeid(mapreduceAPI::DataChunk), MessageType::DataChunk},
    {typeid(mapreduceAPI::JobStatusRequest), MessageType::JobStatusRequest},
    {typeid(mapreduceAPI::JobStatusResponse), MessageType::JobStatusResponse},
    {typeid(mapreduceAPI::JobDeletionApproval), MessageType::JobDeletionApproval}};

inline int send_proto(tcp::socket &socket, google::protobuf::Message &message)
{
  u_int8_t message_type{to_underlying(type_mapping.at(typeid(message)))};
  u_int64_t message_size{message.ByteSizeLong()};

  asio::write(socket, buffer(&message_type, sizeof(message_type)));
  asio::write(socket, buffer(&message_size, sizeof(message_type)));

  streambuf stream_buffer;
  ostream output_stream(&stream_buffer);
  message.SerializeToOstream(&output_stream);
  asio::write(socket, stream_buffer);

  return SEND_OK;
}

inline int receive_proto_message_type(tcp::socket &socket, MessageType &message_type)
{
  u_int8_t raw_message_type;

  socket.receive(buffer(&raw_message_type, sizeof(raw_message_type)), 0);
  message_type = static_cast<MessageType>(message_type);

  return SEND_OK;
}

inline int receive_proto_message(tcp::socket &socket, google::protobuf::Message &message)
{
  u_int64_t message_size;
  socket.receive(buffer(&message_size, sizeof(message_size)), 0);

  streambuf stream_buffer;
  streambuf::mutable_buffers_type mutable_buffer{stream_buffer.prepare(message_size)};

  stream_buffer.commit(read(socket, mutable_buffer));

  istream input_stream{&stream_buffer};
  message.ParseFromIstream(&input_stream);

  return SEND_OK;
}
}