// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "..\..\Service\pch.hpp"

#include "TCPClient.hpp"
#include "..\Protocols\CommandMessageProtocol.hpp"
#include "..\..\Service\Debugger.hpp"
#include "..\..\Service\Log.hpp"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
TCPClient::TCPClient(boost::asio::io_context &io_context, const boost::asio::ip::tcp::resolver::results_type &endpoint) :
	TCPConnection{ io_context },
	m_endpoint   { endpoint }
{ }

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void TCPClient::connect()
{ 
	boost::system::error_code ec;

	this->m_socket.connect(*m_endpoint, ec); 
	if (!ec)
	{
		LOG(info) << "Connected via TCP: " << this->m_socket.remote_endpoint();

		this->m_connected = true;

		this->read_header();
	}
	else
		PrintBoostError(ec);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void TCPClient::async_connect()
{
	boost::asio::async_connect(this->m_socket, m_endpoint,
		[this](const boost::system::error_code &ec, [[maybe_unused]] const boost::asio::ip::tcp::endpoint &endpoint)
		{
			if (!ec)
			{
				LOG(info) << "Connected via TCP: " << endpoint;

				this->m_connected = true;

				this->read_header();
			}
			else
				PrintBoostError(ec);
		});
}


