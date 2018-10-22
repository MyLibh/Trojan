#pragma once

#ifndef __UDPSERVER_HPP_INCLUDED__
#define __UDPSERVER_HPP_INCLUDED__

class CommandMessageProtocol;
using CMPROTO = CommandMessageProtocol;

class UDPServer
{
public:
	UDPServer(boost::asio::io_context &io_context, unsigned short port);
	~UDPServer();

private:
	void setup_new_connection();

private:
	boost::asio::ip::udp::socket    m_socket;
	boost::asio::ip::udp::endpoint  m_endpoint;
	CMPROTO                        *m_msg;
};

#endif /* __UDPSERVER_HPP_INCLUDED__ */