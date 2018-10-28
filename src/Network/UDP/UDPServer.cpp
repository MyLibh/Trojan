// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "..\..\Service\pch.hpp"

#include "UDPServer.hpp"
#include "..\Protocols\CommandMessageProtocol.hpp"
#include "..\..\Service\Debugger.hpp"
#include "..\..\Server\CommandManager.hpp"

UDPServer::UDPServer(boost::asio::io_context &io_context, unsigned short port) :
	m_socket{ io_context, { boost::asio::ip::udp::v4(), port } },
	m_endpoint{},
	m_msg{ new CMPROTO }
{ 
	// m_socket.set_option(boost::asio::socket_base::broadcast(true));

	setup_new_connection();
}

UDPServer::~UDPServer() noexcept = default;

void UDPServer::setup_new_connection()
{
	m_socket.async_receive_from(boost::asio::buffer(m_msg->get_data().data(), m_msg->get_length()), m_endpoint,
		[this](const boost::system::error_code &ec, std::size_t /* bytes_transferred */)
		{
			if (!ec)
			{
				$INFO("New connection via UDP: %s:%d\n", m_endpoint.address().to_string().c_str(), m_endpoint.port())

				m_msg->decode_header();
				CommandManager::execute_command(m_msg, m_socket.get_io_context(), m_endpoint);
			}
			else
				PrintBoostError(ec);

			setup_new_connection();
		});
}