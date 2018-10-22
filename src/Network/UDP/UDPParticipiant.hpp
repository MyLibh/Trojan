#pragma once

#ifndef __UDPPARTICIPIANT_HPP_INCLUDED__
#define __UDPPARTICIPIANT_HPP_INCLUDED__

class CommandMessageProtocol;
using CMPROTO = CommandMessageProtocol;

class ImageMessageProtocol;
using IMPROTO = ImageMessageProtocol;

class UDPParticipiant
{ 
public:
	inline static constexpr std::string_view OK_MESSAGE{ "OK" };

	UDPParticipiant(boost::asio::io_context &io_context, const boost::asio::ip::udp::endpoint &endpoint);

	void send(const CMPROTO *msg);
	void recv(CMPROTO *msg);

	void send(const IMPROTO *msg);
	void recv(IMPROTO *msg);

protected:
	boost::asio::ip::udp::socket   m_socket;
	boost::asio::ip::udp::endpoint m_endpoint;
};

#endif /* __UDPPARTICIPIANT_HPP_INCLUDED__ */