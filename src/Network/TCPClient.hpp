#pragma once

#ifndef __TCPCLIENT_HPP_INCLUDED__
#define __TCPCLIENT_HPP_INCLUDED__

class CommandMessageProtocol;
using CMPROTO = CommandMessageProtocol;

using msg_queue_t = std::deque<CMPROTO*>;

class TCPClient
{
public:
	TCPClient(boost::asio::io_context &io_context, const boost::asio::ip::tcp::resolver::results_type &endpoints);
	~TCPClient();

	void write(const CMPROTO *msg);
	void close();

private:
	void connect(const boost::asio::ip::tcp::resolver::results_type &cr_endpoints);
	void read_header();
	void read_body();
	void write();

private:
	boost::asio::io_context      &m_io;
	boost::asio::ip::tcp::socket  m_socket;
	CMPROTO                      *m_read_msg;
	msg_queue_t                   m_write_msgs;
};

#endif /* __TCPCLIENT_HPP_INCLUDED__ */