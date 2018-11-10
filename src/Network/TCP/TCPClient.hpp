#pragma once

#ifndef __TCPCLIENT_HPP_INCLUDED__
#define __TCPCLIENT_HPP_INCLUDED__

#include "TCPConnection.hpp"

class TCPClient : public TCPConnection 
{
public:
	TCPClient(boost::asio::io_context &io_context, const boost::asio::ip::tcp::endpoint &endpoint);

	void connect(); 
	void async_connect();

private:
	boost::asio::ip::tcp::endpoint m_endpoint;
};

#endif /* __TCPCLIENT_HPP_INCLUDED__ */