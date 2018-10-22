// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "..\..\Service\pch.hpp"

#include "UDPParticipiant.hpp"
#include "..\Protocols\CommandMessageProtocol.hpp"
#include "..\Protocols\ImageMessageProtocol.hpp"
#include "..\..\Service\Debugger.hpp"

UDPParticipiant::UDPParticipiant(boost::asio::io_context &io_context, const boost::asio::ip::udp::endpoint &endpoint) :
	m_socket{ io_context, endpoint },
	m_endpoint{ endpoint }
{
	// m_socket.set_option(boost::asio::socket_base::broadcast(true));
}

void UDPParticipiant::send(const CMPROTO *msg)
{
	std::cout << m_endpoint;
	while(m_socket.send_to(boost::asio::buffer(msg->get_data(), msg->get_length()), m_endpoint) != msg->get_length());
}

void UDPParticipiant::recv(CMPROTO *msg)
{
	m_socket.receive_from(boost::asio::buffer(msg->get_data(), msg->get_length()), m_endpoint);

	msg->decode_header();
}

void UDPParticipiant::send(const IMPROTO *msg)
{
	for (size_t i{}; i < msg->get_chunk_num(); ++i)
	{
	start:
		const_cast<IMPROTO*>(msg)->encode_header(i);
		m_socket.send_to(boost::asio::buffer(const_cast<IMPROTO*>(msg)->get_chunk(i), msg->get_chunk_size(i)), m_endpoint);

		if (!i)
		{
			char buff[OK_MESSAGE.length() + 1]{ };
			m_socket.receive_from(boost::asio::buffer(buff, OK_MESSAGE.length()), m_endpoint);
			if (buff != OK_MESSAGE)
				goto start;
		}
	}
}

void UDPParticipiant::recv(IMPROTO *msg)
{
	for (size_t i{}; i < msg->get_chunk_num(); ++i)
	{
		msg->decode_header(i);

		if (!i)
		{
			m_socket.send_to(boost::asio::buffer(OK_MESSAGE, OK_MESSAGE.length()), m_endpoint);

			continue;
		}

		m_socket.receive_from(boost::asio::buffer(msg->get_chunk(i), msg->get_chunk_size(i)), m_endpoint);
	}
}