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

Application::Application(const std::string &ip, const std::string &port) :
	m_io(),
	m_tcp_client(new TCPClient(m_io, boost::asio::ip::tcp::resolver(m_io).resolve(ip, port))),
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
	std::string command;
	while (std::getline(std::cin, command))
		send_command(command);
}

void Application::send_command(const std::string &command)
{
	static CMPROTO msg;

	size_t separator_pos = command.find_first_of(' ');
	auto   cmd_line      = command.substr(0, separator_pos);
	auto   args          = command.substr(separator_pos + 1);

	msg.clear_data();
	msg.set_body_length(CMPROTO::COMMAND_LENGTH + CMPROTO::SPACE_LENGTH + args.length());
	if (auto iter = std::find_if(std::begin(COMMAND_PROPERTIES), std::end(COMMAND_PROPERTIES), [&cmd_line](const auto &prop) { return (cmd_line == std::get<1>(prop.command)); }); iter != std::end(COMMAND_PROPERTIES))
	{
		char buff[CMPROTO::COMMAND_LENGTH + CMPROTO::SPACE_LENGTH + 1] = "";
		int cmd = static_cast<int>(std::get<Commands>(iter->command));
		sprintf_s(buff, "%2d ", cmd);

		std::memcpy(msg.get_body(), buff, CMPROTO::COMMAND_LENGTH + CMPROTO::SPACE_LENGTH);
		std::memcpy(msg.get_args(), args.c_str(), CMPROTO::MAX_ARGS_LENGTH);

		msg.encode_header();

		m_tcp_client->write(&msg);
	}
	else
		$ERROR(TEXTH("Wrong Command: '%s'\n"), command.c_str());
}

void Application::close()
{
	m_tcp_client->close();
	m_thread.join();
}
