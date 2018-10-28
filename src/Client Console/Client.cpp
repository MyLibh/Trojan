// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "..\Service\pch.hpp"

#include "Client.hpp"
#include "..\Network\TCP\TCPClient.hpp"
#include "..\Network\Protocols\CommandMessageProtocol.hpp"
#include "..\Server\CommandProperties.hpp"
#include "..\Service\Debugger.hpp"
#include "..\Network\UDP\UDPClient.hpp"
#include "..\Service\Constants.hpp"
#include "..\Service\Log.hpp"

Client::Client() noexcept :
	m_io        { },
	m_tcp_client{ nullptr },
	m_udp_client{ nullptr },
	m_thread    { }
{ }

Client::~Client() noexcept = default;

void Client::init()
{
	m_tcp_client = std::make_unique<TCPClient>(m_io, boost::asio::ip::tcp::resolver(m_io).resolve(SERVER_IP, DEFAULT_PORT));
	m_udp_client = std::make_unique<UDPClient>(m_io, boost::asio::ip::udp::resolver(m_io).resolve(SERVER_IP, DEFAULT_PORT));
	m_thread     = std::thread{ [this]() { m_io.run(); } };
} 

void Client::init(std::string_view ip, std::string_view port)
{
	m_tcp_client = std::make_unique<TCPClient>(m_io, boost::asio::ip::tcp::resolver(m_io).resolve(ip, port));
	m_udp_client = std::make_unique<UDPClient>(m_io, boost::asio::ip::udp::resolver(m_io).resolve(ip, port));
	m_thread     = std::thread{ [this]() { m_io.run(); } };
}

void Client::run()
{
	std::string command;
	while (std::getline(std::cin, command))
		send_command(command);
}

void Client::send_command(std::string_view command)
{
	std::size_t separator_pos = command.find_first_of(' ');
	if (separator_pos == std::string::npos)
		separator_pos = command.length();

	auto cmd_line = command.substr(0, separator_pos);
	auto args     = command.substr(separator_pos);

#pragma warning(suppress : 26486)
	// Don't pass a pointer that may be invalid to a function (lifetime.1).
	if(!args.empty() && cmd_line.compare(args))
		args = "";

	std::shared_ptr<CMPROTO> msg{ std::make_shared<CMPROTO>() };
	msg->set_body_length(CMPROTO::COMMAND_LENGTH + (args.empty() ? 0 : CMPROTO::SPACE_LENGTH + args.length()));
	if (auto iter = std::find_if(std::begin(COMMAND_PROPERTIES), std::end(COMMAND_PROPERTIES), [&cmd_line](const auto &prop) { return (cmd_line == std::get<1>(prop.command)); }); iter != std::end(COMMAND_PROPERTIES))
	{	
		// Translate command
		char buff[CMPROTO::COMMAND_LENGTH + 1]{ };
		const int cmd = static_cast<int>(std::get<Commands>(iter->command));
		sprintf_s(buff, "%2d", cmd);

		// Copy full command 
		memcpy_s(msg->get_body().data(), CMPROTO::MAX_BODY_LENGTH,        buff, CMPROTO::COMMAND_LENGTH);
		memcpy_s(msg->get_args().data(), CMPROTO::MAX_ARGS_LENGTH, args.data(), CMPROTO::MAX_ARGS_LENGTH);

		msg->encode_header();

		if (iter->exec_func.index() == 0)
			m_tcp_client->write(msg);
		else
			m_udp_client->send(msg);
	}
	else
		LOG(error) << "Wrong Command: '" << command.data() << "'";
}

void Client::close()
{
	m_tcp_client->close();
	m_thread.join();
}
