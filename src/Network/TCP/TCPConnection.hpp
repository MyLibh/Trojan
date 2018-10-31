#pragma once

#ifndef __TCPCONNECTION_HPP_INCLUDED__
#define __TCPCONNECTION_HPP_INCLUDED__

class CommandMessageProtocol;
using CMPROTO = CommandMessageProtocol;

using msg_queue_t = std::deque<std::unique_ptr<CMPROTO>>;

class TCPConnection : private boost::noncopyable
{
public:
	TCPConnection(boost::asio::io_context &io_context);
#pragma warning(suppress : 26432)
	// warning C26432: If you define or delete any default operation in the type 'class TCPConnection', define or delete them all (c.21).
	virtual ~TCPConnection() noexcept;

	virtual void write(std::unique_ptr<CMPROTO> &&msg);
	virtual void close();

protected:
	virtual void read_header();
	virtual void read_body();
	virtual void write();
	
protected:
	boost::asio::io_context      &m_io;
	boost::asio::ip::tcp::socket  m_socket;
	bool                          m_connected;
	std::unique_ptr<CMPROTO>      m_read_msg;
	msg_queue_t                   m_write_msgs;
};

#endif /* __TCPCONNECTION_HPP_INCLUDED__ */