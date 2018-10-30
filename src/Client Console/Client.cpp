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
	std::size_t separator_pos{ command.find_first_of(' ') };
	if (separator_pos == std::string::npos)
		separator_pos = command.length();

	auto cmd_line{ command.substr(0, separator_pos) };
	auto args    { command.substr(separator_pos) };

	std::unique_ptr<CMPROTO> msg{ std::make_unique<CMPROTO>() };
	msg->set_body_length(CMPROTO::COMMAND_LENGTH + (args.empty() ? 0 : CMPROTO::SPACE_LENGTH + args.length()));
	if (auto iter = std::find_if(std::begin(COMMAND_PROPERTIES), std::end(COMMAND_PROPERTIES), [&cmd_line](const auto &prop) { return (cmd_line == std::get<1>(prop.command)); }); iter != std::end(COMMAND_PROPERTIES))
	{
		// Translate command
		char      buff[CMPROTO::COMMAND_LENGTH + 1]{ };                                                     // buffer which contains translated command
		const int cmd                              { static_cast<int>(std::get<Commands>(iter->command)) }; // translated command

		sprintf_s(buff, "%2d", cmd);

		// Copy full command 
		std::copy_n(std::begin(buff), CMPROTO::COMMAND_LENGTH, msg->get_body());
		std::copy(std::begin(args), std::end(args), msg->get_args());

		msg->encode_header();

		if (iter->exec_func.index() == 0)
			m_tcp_client->write(std::move(msg));
		//else
			//m_udp_client->send(msg);
	}
	else
		LOG(error) << "Wrong Command: '" << command.data() << "'";
}

// =IMPORTRANGE("https://docs.google.com/spreadsheets/d/1AYy515x2Pt2CRVlqi_BPxtULZZVNRlaQhXFjEwm1BtQ/edit";"Лист1!A1:CC1")
// =IMPORTRANGE("https://docs.google.com/spreadsheets/d/1AYy515x2Pt2CRVlqi_BPxtULZZVNRlaQhXFjEwm1BtQ/edit";"Лист1!A1:CC1")

void Client::close()
{
	m_tcp_client->close();
	m_thread.join();
}
