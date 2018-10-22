#pragma once

#ifndef __TCPCLIENT_HPP_INCLUDED__
#define __TCPCLIENT_HPP_INCLUDED__

#include "TCPConnection.hpp"

class TCPClient final : public TCPConnection
{
public:
	TCPClient(boost::asio::io_context &io_context, const boost::asio::ip::tcp::resolver::results_type &endpoints);

private:
	void connect(const boost::asio::ip::tcp::resolver::results_type &cr_endpoints);
};

#endif /* __TCPCLIENT_HPP_INCLUDED__ */