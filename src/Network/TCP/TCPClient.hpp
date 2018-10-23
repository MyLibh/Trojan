#pragma once

#ifndef __TCPCLIENT_HPP_INCLUDED__
#define __TCPCLIENT_HPP_INCLUDED__

#include "TCPConnection.hpp"

class TCPClient : public TCPConnection 
{
public:
	TCPClient(boost::asio::io_context &io_context, const boost::asio::ip::tcp::resolver::results_type &endpoint);
	~TCPClient() = default;

private:
	void connect(const boost::asio::ip::tcp::resolver::results_type &endpoint);
};

#endif /* __TCPCLIENT_HPP_INCLUDED__ */