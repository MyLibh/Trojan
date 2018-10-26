// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "..\Service\pch.hpp"

#include "Application.hpp"
#include "..\Network\TCP\TCPClient.hpp"
#include "..\Network\Protocols\CommandMessageProtocol.hpp"
#include "..\Server\CommandProperties.hpp"
#include "..\Service\Debugger.hpp"
#include "..\Network\UDP\UDPClient.hpp"
#include "..\Service\Constants.hpp"
#include "..\Service\Log.hpp"

Application::Application() noexcept :
	m_io{ },
	m_tcp_client{ },
	m_udp_client{ },
	m_thread{ }
{ }

Application::~Application()
{ }

void Application::init()
{
	m_tcp_client = std::make_unique<TCPClient>(m_io, boost::asio::ip::tcp::resolver(m_io).resolve(SERVER_IP, DEFAULT_PORT));
	m_udp_client = std::make_unique<UDPClient>(m_io, boost::asio::ip::udp::resolver(m_io).resolve(SERVER_IP, DEFAULT_PORT));
	m_thread     = std::thread{ [this]() { m_io.run(); } };
} 

#pragma warning(push)
//#pragma warning(disable : ) 
void Application::init(const char **argv)
{
	m_tcp_client = std::make_unique<TCPClient>(m_io, boost::asio::ip::tcp::resolver(m_io).resolve(argv[1], argv[2]));
	m_udp_client = std::make_unique<UDPClient>(m_io, boost::asio::ip::udp::resolver(m_io).resolve(argv[1], argv[2]));
	m_thread     = std::thread{ [this]() { m_io.run(); } };
}
#pragma warning(pop)

void Application::init(std::string_view ip, std::string_view port)
{
	m_tcp_client = std::make_unique<TCPClient>(m_io, boost::asio::ip::tcp::resolver(m_io).resolve(ip, port));
	m_udp_client = std::make_unique<UDPClient>(m_io, boost::asio::ip::udp::resolver(m_io).resolve(ip, port));
	m_thread     = std::thread{ [this]() { m_io.run(); } };
}

void Application::run()
{
	std::string command;
	while (std::getline(std::cin, command))
		send_command(command);
}

void Application::send_command(std::string_view command)
{
	static CMPROTO msg;
	msg.clear_data();

	size_t separator_pos = command.find_first_of(' ');
	if (separator_pos == std::string::npos)
		separator_pos = command.length();

	auto cmd_line = command.substr(0, separator_pos);
	auto args     = command.substr(separator_pos);
	if (cmd_line == args)
		args = "";

	msg.set_body_length(CMPROTO::COMMAND_LENGTH + (args.empty() ? 0 : CMPROTO::SPACE_LENGTH + args.length()));
	if (auto iter = std::find_if(std::begin(COMMAND_PROPERTIES), std::end(COMMAND_PROPERTIES), [&cmd_line](const auto &prop) { return (cmd_line == std::get<1>(prop.command)); }); iter != std::end(COMMAND_PROPERTIES))
	{	
		// Translate command
		char buff[CMPROTO::COMMAND_LENGTH + 1]{ };
		const int cmd = static_cast<int>(std::get<Commands>(iter->command));
		sprintf_s(buff, "%2d", cmd);

		// Copy full command 
		std::memcpy(msg.get_body().data(), buff, CMPROTO::COMMAND_LENGTH);
		std::memcpy(msg.get_args().data(), args.data(), CMPROTO::MAX_ARGS_LENGTH);

		msg.encode_header();

		if (iter->exec_func.index() == 0)
			m_tcp_client->write(&msg);
		else
			m_udp_client->send(&msg);
	}
	else
		LOG(error) << "Wrong Command: '" << command.data() << "'";
}

void Application::close()
{
	m_tcp_client->close();
	m_thread.join();
}
