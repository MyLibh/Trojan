// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "..\..\Service\pch.hpp"

#include "UDPParticipiant.hpp"
#include "..\Protocols\CommandMessageProtocol.hpp"
#include "..\Protocols\ImageMessageProtocol.hpp"
#include "..\..\Service\Debugger.hpp"

UDPParticipiant::UDPParticipiant(boost::asio::io_context &io_context, const boost::asio::ip::udp::endpoint &endpoint) :
	m_socket  { io_context, endpoint },
	m_endpoint{ endpoint }
{
	// m_socket.set_option(boost::asio::socket_base::broadcast(true));
}

/*************************************************************************************************************************************************************************************************************/
void UDPParticipiant::send(std::unique_ptr<CMPROTO> &&msg)
{
	while(m_socket.send_to(boost::asio::buffer(msg->get_data().data(), msg->get_length()), m_endpoint) != msg->get_length());
}

/*************************************************************************************************************************************************************************************************************/
void UDPParticipiant::recv(std::unique_ptr<CMPROTO> &msg)
{
	while(m_socket.receive_from(boost::asio::buffer(msg->get_data().data(), msg->get_length()), m_endpoint) != msg->get_length());

	msg->decode_header();
}

#pragma warning(suppress : 26415 26418)
// warning C26415: Smart pointer parameter 'msg' is used only to access contained pointer. Use T* or T& instead (r.30).
// warning C26418: Shared pointer parameter 'msg' is not copied or moved. Use T* or T& instead (r.36).
void UDPParticipiant::send(const std::shared_ptr<IMPROTO> &msg)
{
	bool send_ok{ };
	for (std::size_t i{ }; i < msg->get_chunk_num();)
	{
		msg->encode_header(i);
		m_socket.send_to(boost::asio::buffer(msg->get_chunk(i), msg->get_chunk_size(i)), m_endpoint);

		if (i == 0 && !send_ok)
		{
			char buff[OK_MESSAGE.length() + 1]{};
			m_socket.receive_from(boost::asio::buffer(buff, OK_MESSAGE.length()), m_endpoint);
			if (buff == OK_MESSAGE)
				send_ok = true;
		}

		if (send_ok)
			++i;
	}
}

#pragma warning(suppress : 26415 26418)
// warning C26415: Smart pointer parameter 'msg' is used only to access contained pointer. Use T* or T& instead (r.30).
// warning C26418: Shared pointer parameter 'msg' is not copied or moved. Use T* or T& instead (r.36).
void UDPParticipiant::recv(const std::shared_ptr<IMPROTO> &msg)
{
	m_socket.receive_from(boost::asio::buffer(msg->get_chunk(0), msg->get_chunk_size(0)), m_endpoint);
	msg->decode_header(0);
	m_socket.send_to(boost::asio::buffer(OK_MESSAGE, OK_MESSAGE.length()), m_endpoint);

	for (std::size_t i{ 1 }; i < msg->get_chunk_num(); ++i)
	{
		m_socket.receive_from(boost::asio::buffer(msg->get_chunk(i), msg->get_chunk_size(i)), m_endpoint);
		msg->decode_header(i);
	}
}