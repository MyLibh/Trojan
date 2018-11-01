// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "..\..\Service\pch.hpp"

#include "TCPServer.hpp"
#include "..\Protocols\CommandMessageProtocol.hpp"
#include "..\..\Service\Debugger.hpp"
#include "..\..\Service\Log.hpp"
#include "..\..\Server\CommandManager.hpp"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
TCPServer::TCPServer(boost::asio::io_context &io_context, unsigned short port) :
	TCPConnection{ io_context },
	m_acceptor   { io_context, { boost::asio::ip::tcp::v4(), port } }
{
	accept();
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void TCPServer::accept()
{
	m_acceptor.async_accept(
		[this](const boost::system::error_code &ec, boost::asio::ip::tcp::socket socket)
		{
			if (!ec)
			{
				LOG(info) << "New connection via TCP: " << socket.remote_endpoint();

				this->m_socket    = std::move(socket);
				this->m_connected = true;

				read_header();
			}
			else
				PrintBoostError(ec);	
		});
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void TCPServer::read_header()
{
	boost::asio::async_read(this->m_socket, boost::asio::buffer(m_read_msg->get_data().data(), CMPROTO::HEADER_LENGTH),
		[this](const boost::system::error_code &ec, [[maybe_unused]] std::size_t length)
		{
			if (!ec)
			{
				LOG(trace) << "Recieved header via TCP(" << length << "): '" << m_read_msg->get_data().data() << '\'';

				if(m_read_msg->decode_header())
					read_body();
			}
			else
			{
				PrintBoostError(ec);

				this->close();
			}
		});
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void TCPServer::read_body()
{
	boost::asio::async_read(this->m_socket, boost::asio::buffer(m_read_msg->get_body().data(), m_read_msg->get_body_length()),
		[this](const boost::system::error_code &ec, [[maybe_unused]] std::size_t length)
		{
			if (!ec)
			{
				LOG(trace) << "Recieved body via TCP(" << length << "): '" << m_read_msg->get_body().data() << '\'';

				std::shared_ptr<CMPROTO> tmp_ptr{ m_read_msg.release() };
				this->write(CommandManager::execute_command(tmp_ptr, this->m_socket.get_io_context(), { }) ? make_success_msg() : make_failure_msg());

				m_read_msg.reset(tmp_ptr.get());
				tmp_ptr.reset();
				m_read_msg->clear_data();
				
				read_header();
			}
			else
			{
				PrintBoostError(ec);

				this->close();
			}
		});
}



