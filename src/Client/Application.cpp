#include "..\Service\pch.hpp"

#include "Application.hpp"
#include "..\Network\TCPClient.hpp"
#include "..\Network\Protocols\CommandMessageProtocol.hpp"
//#include "..\Network\UDPParticipiant.hpp"
//#include "..\Network\Protocols\DesktopImageMessageProtocol.hpp"
#include "..\Server\CommandProperties.hpp"
#include "..\Service\Debugger.hpp"

Application::Application() :
	m_io(),
	m_tcp_client(new TCPClient(m_io, boost::asio::ip::tcp::resolver(m_io).resolve(SERVER_IP, DEFAULT_PORT))),
	/*m_udp_participiant(new UDPParticipiant(m_io, boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(SERVER_IP), std::atoi(DEFAULT_PORT)))),*/
	m_thread([this]() { m_io.run(); })
{ }

Application::Application(char *argv[]) :
	m_io(),
	m_tcp_client(new TCPClient(m_io, boost::asio::ip::tcp::resolver(m_io).resolve(argv[1], argv[2]))),
	/*m_udp_participiant(new UDPParticipiant(m_io, boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(argv[1]), std::atoi(argv[2])))),*/
	m_thread([this]() { m_io.run(); })
{ }

Application::~Application()
{
	delete m_tcp_client;
	//delete m_udp_participiant;
}

void Application::run()
{
	char line[CMPROTO::MAX_BODY_LENGTH + 1] = "";
	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		std::string command;
		std::cin >> command; 
		std::cin.getline(line, CMPROTO::MAX_BODY_LENGTH - CMPROTO::COMMAND_LENGTH); //  - CMPROTO::SPACE_LENGTH + 1 = 0

		CMPROTO msg;
		msg.set_body_length(std::strlen(line) + CMPROTO::COMMAND_LENGTH + CMPROTO::SPACE_LENGTH);
		if (auto iter = std::find_if(std::begin(COMMAND_PROPERTIES), std::end(COMMAND_PROPERTIES), [&command](const auto &prop) { return (command == std::get<1>(prop.command)); }); iter != std::end(COMMAND_PROPERTIES))
		{
			char buff[CMPROTO::COMMAND_LENGTH + CMPROTO::SPACE_LENGTH + 1] = "";
			int cmd = static_cast<int>(std::get<Commands>(iter->command));
			sprintf_s(buff, "%2d ", cmd);

			std::memcpy(msg.get_body(), buff, CMPROTO::COMMAND_LENGTH + CMPROTO::SPACE_LENGTH);
			std::memcpy(msg.get_args(), line, msg.get_body_length());

			msg.encode_header();

			m_tcp_client->write(&msg);
		}
		else 
		{
			$ERROR("Wrong Command: '%s'\n", command.c_str());
		}
	}
}

void Application::close()
{
	m_tcp_client->close();
	m_thread.join();
}
