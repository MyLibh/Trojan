#pragma once

#ifndef __UDPPARTICIPIANT_HPP_INCLUDED__
#define __UDPPARTICIPIANT_HPP_INCLUDED__

class DesktopImageMessageProtocol;
using DIMPROTO = DesktopImageMessageProtocol;

class UDPParticipiant
{
public:
	static constexpr std::string_view OK_MESSAGE = "OK";

	UDPParticipiant(boost::asio::io_context &io_context, const boost::asio::ip::udp::endpoint &endpoint);

	void send(DIMPROTO &msg);
	void recv(DIMPROTO &msg);

private:
	boost::asio::ip::udp::socket    m_socket;
	boost::asio::ip::udp::endpoint  m_endpoint;
};

#endif /* __UDPPARTICIPIANT_HPP_INCLUDED__ */