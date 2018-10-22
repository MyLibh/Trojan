#pragma once

#ifndef __UDPPARTICIPIANT_HPP_INCLUDED__
#define __UDPPARTICIPIANT_HPP_INCLUDED__

#include "Protocols/ImageMessageProtocol.hpp"

using IMPROTO = ImageMessageProtocol;

template<typename MPROTO = IMPROTO>
class UDPParticipiant
{ 
public:
	inline static constexpr std::string_view OK_MESSAGE{ "OK" };

	UDPParticipiant(boost::asio::io_context &io_context, const boost::asio::ip::udp::endpoint &endpoint);

	void send(MPROTO &msg);
	void recv(MPROTO &msg);

protected:
	boost::asio::ip::udp::socket   m_socket;
	boost::asio::ip::udp::endpoint m_endpoint;
};

#pragma region IMPROTO specialization(the same as default)

template<typename MPROTO>
UDPParticipiant<MPROTO>::UDPParticipiant(boost::asio::io_context &io_context, const boost::asio::ip::udp::endpoint &endpoint) :
	m_socket(io_context, endpoint),
	m_endpoint(endpoint)
{
	m_socket.set_option(boost::asio::socket_base::broadcast(true));
}

template<typename MPROTO>
void UDPParticipiant<MPROTO>::send(MPROTO &msg)
{
	for (size_t i{}; i < msg.get_chunk_num(); ++i)
	{
	start:
		msg.encode_header(i);
		m_socket.send_to(boost::asio::buffer(msg.get_chunk(i), msg.get_chunk_size(i)), m_endpoint);

		if (!i)
		{
			char buff[OK_MESSAGE.length() + 1] = "";
			m_socket.receive_from(boost::asio::buffer(buff, OK_MESSAGE.length()), m_endpoint);
			if (buff != OK_MESSAGE)
				goto start;
		}
	}
}

template<typename MPROTO>
void UDPParticipiant<MPROTO>::recv(MPROTO &msg)
{
	for (size_t i{}; i < msg.get_chunk_num(); ++i)
	{
		msg.decode_header(i);

		if (!i)
		{
			m_socket.send_to(boost::asio::buffer(OK_MESSAGE, OK_MESSAGE.length()), m_endpoint);

			continue;
		}

		m_socket.receive_from(boost::asio::buffer(msg.get_chunk(i), msg.get_chunk_size(i)), m_endpoint);
	}
}

#pragma endregion 

#endif /* __UDPPARTICIPIANT_HPP_INCLUDED__ */