#pragma once

#ifndef __UDPPARTICIPIANT_HPP_INCLUDED__
#define __UDPPARTICIPIANT_HPP_INCLUDED__

#include "Protocols/ImageMessageProtocol.hpp"

template<typename MPROTO>
class IUDPParticipiant
{ 
public:
	inline static constexpr std::string_view OK_MESSAGE{ "OK" };

	IUDPParticipiant(boost::asio::io_context &io_context, const boost::asio::ip::udp::endpoint &endpoint);

	void send(MPROTO &msg);
	void recv(MPROTO &msg);

protected:
	boost::asio::ip::udp::socket   m_socket;
	boost::asio::ip::udp::endpoint m_endpoint;
};

#pragma region IMPROTO specialization

using IMPROTO = ImageMessageProtocol;

template<>
IUDPParticipiant<IMPROTO>::IUDPParticipiant(boost::asio::io_context &io_context, const boost::asio::ip::udp::endpoint &endpoint) :
	m_socket(io_context, endpoint),
	m_endpoint(endpoint)
{
	m_socket.set_option(boost::asio::socket_base::broadcast(true));
}

template<>
void IUDPParticipiant<IMPROTO>::send(IMPROTO &msg)
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

template<>
void IUDPParticipiant<IMPROTO>::recv(IMPROTO &msg)
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