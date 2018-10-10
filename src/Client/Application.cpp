#include "..\Service\pch.hpp"

#include "Application.hpp"
#include "..\Service\Constants.h"
#include "..\Network\TCPClient.hpp"
#include "..\Network\Protocols\CommandMessageProtocol.hpp"
#include "..\Network\UDPParticipiant.hpp"
#include "..\Network\Protocols\DesktopImageMessageProtocol.hpp"

Application::Application() :
	m_io(),
	m_tcp_client(new TCPClient(m_io, boost::asio::ip::tcp::resolver(m_io).resolve(SERVER_IP, DEFAULT_PORT))),
	m_udp_participiant(new UDPParticipiant(m_io, boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(SERVER_IP), std::atoi(DEFAULT_PORT)))),
	m_thread([this]() { m_io.run(); })
{ }

Application::Application(char *argv[]) :
	m_io(),
	m_tcp_client(new TCPClient(m_io, boost::asio::ip::tcp::resolver(m_io).resolve(argv[1], argv[2]))),
	m_udp_participiant(new UDPParticipiant(m_io, boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(argv[1]), std::atoi(argv[2])))),
	m_thread([this]() { m_io.run(); })
{ }

Application::~Application()
{
	delete m_tcp_client;
	delete m_udp_participiant;
}

void Application::run()
{
	char line[CMPROTO::MAX_BODY_LENGTH + 1] = "";
	while (std::cin.getline(line, CMPROTO::MAX_BODY_LENGTH + 1))
	{
		CMPROTO msg;
		msg.set_body_length(std::strlen(line));
		std::memcpy(msg.get_body(), line, msg.get_body_length());
		msg.encode_header();

		m_tcp_client->write(&msg);
	}
}

void Application::close()
{
	m_tcp_client->close();
	m_thread.join();
}
