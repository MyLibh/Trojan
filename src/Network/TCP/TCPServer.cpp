// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "..\..\Service\pch.hpp"

#include "TCPServer.hpp"
#include "..\Protocols\CommandMessageProtocol.hpp"
#include "..\..\Service\Debugger.hpp"
#include "..\..\Server\CommandManager.hpp"

TCPServer::TCPServer(boost::asio::io_context &io_context, unsigned short port) :
	TCPConnection{ io_context },
	m_acceptor{ io_context, { boost::asio::ip::tcp::v4(), port } }
{
	accept();
}

void TCPServer::accept()
{
	m_acceptor.async_accept(
		[this](const boost::system::error_code &ec, boost::asio::ip::tcp::socket socket)
		{
			if (!ec)
			{
				m_socket = std::move(socket);

				$INFO("New connection via TCP: %s:%d\n", m_socket.remote_endpoint().address().to_string().c_str(), m_socket.remote_endpoint().port())

				m_connected = true;
			}
			else
				PrintBoostError(ec);

			read_header();
		});
}

void TCPServer::read_header()
{
	boost::asio::async_read(m_socket, boost::asio::buffer(m_read_msg->get_data(), CMPROTO::HEADER_LENGTH),
		[this](const boost::system::error_code &ec, size_t /* length */)
		{
			if (!ec && m_read_msg->decode_header())
				read_body();
			else
			{
				PrintBoostError(ec);

				close();
			}
		});
}

void TCPServer::read_body()
{
	boost::asio::async_read(m_socket, boost::asio::buffer(m_read_msg->get_body(), m_read_msg->get_body_length()),
		[this](const boost::system::error_code &ec, size_t /* length */)
		{
			if (!ec)
			{
				write(&(CommandManager::execute_command(m_read_msg, m_socket.get_io_context(), { }) ? CMPROTO_RESULT_SUCCESS : CMPROTO_RESULT_FAILURE));

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


