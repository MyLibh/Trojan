#pragma once

#ifndef __UDPCLIENT_HPP_INCLUDED__
#define __UDPCLIENT_HPP_INCLUDED__

class CommandMessageProtocol;
using CMPROTO = CommandMessageProtocol;

class UDPClient : private boost::noncopyable
{
public:
	UDPClient(boost::asio::io_context &io_context, const boost::asio::ip::udp::resolver::results_type &endpoint);
	~UDPClient() = default;

	void send(const CMPROTO *msg);

private:
	boost::asio::io_context        &m_io;
	boost::asio::ip::udp::endpoint  m_endpoint;
};

#endif /* __UDPCLIENT_HPP_INCLUDED__ */