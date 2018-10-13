#include "..\Service\pch.hpp"

#include "TCPClient.hpp"
#include "Protocols\CommandMessageProtocol.hpp"
#include "..\Service\Debugger.hpp"

TCPClient::TCPClient(boost::asio::io_context &io_context, const boost::asio::ip::tcp::resolver::results_type &endpoints) :
	TCPConnection(io_context)
{
	connect(endpoints);
}

void TCPClient::connect(const boost::asio::ip::tcp::resolver::results_type &endpoints)
{
	boost::asio::async_connect(m_socket, endpoints,
		[this](boost::system::error_code ec, boost::asio::ip::tcp::endpoint /* endpoint */)
		{
			if (!ec)
			{
				m_connected = true;

				read_header();
			}
			else
				PrintBoostError(ec);
		});
}


