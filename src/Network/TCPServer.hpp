#pragma once

#ifndef __TCPSERVER_HPP_INCLUDED__
#define __TCPSERVER_HPP_INCLUDED__

#include "TCPConnection.hpp"

class CommandManager;

class TCPServer final : public TCPConnection
{
public:
	TCPServer(boost::asio::io_context &io_context, const boost::asio::ip::tcp::endpoint &endpoint);
	~TCPServer();

private:
	void accept();
	virtual void read_header() override final;
	virtual void read_body() override final;

private:
	boost::asio::ip::tcp::acceptor  m_acceptor;
	CommandManager                 *m_cmd_manager;
};

#endif /* __TCPSERVER_HPP_INCLUDED__ */