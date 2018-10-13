#pragma once

#ifndef __TCPCONNECTION_HPP_INCLUDED__
#define __TCPCONNECTION_HPP_INCLUDED__

class CommandMessageProtocol;
using CMPROTO = CommandMessageProtocol;

using msg_queue_t = std::deque<CMPROTO*>;

class TCPConnection abstract
{
public:
	TCPConnection(boost::asio::io_context &io_context);
	~TCPConnection();

	TCPConnection(const TCPConnection&) = delete;
	TCPConnection& operator=(const TCPConnection&) = delete;

	virtual void write(const CMPROTO *msg);
	virtual void close();

protected:
	virtual void read_header();
	virtual void read_body();
	virtual void write();

protected:
	boost::asio::io_context      &m_io;
	boost::asio::ip::tcp::socket  m_socket;
	bool                          m_connected;
	CMPROTO                      *m_read_msg;
	msg_queue_t                   m_write_msgs;
};

#endif /* __TCPCONNECTION_HPP_INCLUDED__ */