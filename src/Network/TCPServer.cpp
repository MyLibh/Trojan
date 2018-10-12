#include "..\Service\pch.hpp"

#include "TCPServer.hpp"
#include "Protocols\CommandMessageProtocol.hpp"
#include "..\Service\Debugger.hpp"
#include "..\Server\CommandManager.hpp"

TCPServer::TCPServer(boost::asio::io_context &io_context, const boost::asio::ip::tcp::endpoint &endpoint) :
	m_io(io_context),
	m_socket(io_context), 
	m_acceptor(io_context, endpoint),
	m_read_msg(new CMPROTO),
	m_write_msgs(),
	m_cmd_manager(new CommandManager)
{
	accept();
}

TCPServer::~TCPServer()
{
	delete m_read_msg;
	delete m_cmd_manager;
}

void TCPServer::write(const CMPROTO *msg)
{
	boost::asio::post(m_io,
		[this, msg]()
		{
			bool write_in_progress = !m_write_msgs.empty();
			m_write_msgs.push_back(const_cast<CMPROTO*>(msg));
			if (!write_in_progress)
				write();
		});
}

void TCPServer::close()
{
	boost::asio::post(m_io,
		[this]()
	{
		m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
		m_socket.close();
	});
}

void TCPServer::accept()
{
	m_acceptor.async_accept(
		[this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket)
	{
		if (!ec)
			m_socket = std::move(socket);
		else
			PrintBoostError(ec);

		read_header();
	});
}

void TCPServer::read_header()
{
	boost::asio::async_read(m_socket, boost::asio::buffer(m_read_msg->get_data(), CMPROTO::HEADER_LENGTH),
		[this](boost::system::error_code ec, size_t /* length */)
		{
			if (!ec && m_read_msg->decode_header())
				read_body();
			else
			{
				PrintBoostError(ec);

				m_socket.close();
			}
		});
}

void TCPServer::read_body()
{
	boost::asio::async_read(m_socket, boost::asio::buffer(m_read_msg->get_body(), m_read_msg->get_body_length()),
		[this](boost::system::error_code ec, size_t /* length */)
		{
			if (!ec)
			{
				write(&(m_cmd_manager->execute_command(m_read_msg) ? CMPROTO_RESULT_SUCCESS : CMPROTO_RESULT_FAILURE));

				m_read_msg->clear_data();

				read_header();
			}
			else
			{
				PrintBoostError(ec);

				m_socket.close();
			}
		});
}

void TCPServer::write()
{
	boost::asio::async_write(m_socket, boost::asio::buffer(m_write_msgs.front()->get_data(), m_write_msgs.front()->get_length()),
		[this](boost::system::error_code ec, size_t /* length */)
		{
			if (!ec)
			{
				m_write_msgs.pop_front();
				if (!m_write_msgs.empty())
					write();
			}
			else
			{
				PrintBoostError(ec);

				m_socket.close();
			}
		});
}


