// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "..\Service\pch.hpp"

#include "Client.hpp"
#include "..\Network\TCP\TCPClient.hpp"
#include "..\Network\UDP\UDPClient.hpp"
#include "..\Network\Protocols\CommandMessageProtocol.hpp"
#include "..\Service\Debugger.hpp"
#include "..\Service\Constants.hpp"
#include "..\Service\Log.hpp"
#include "..\Server\CommandProperties.hpp"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Client::Client() noexcept :
	m_io        { },
	m_tcp_client{ nullptr },
	m_udp_client{ nullptr },
	m_thread    { }
{ }

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Client::~Client() noexcept = default;

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Client::init(std::string_view ip, std::string_view port)
{
	m_tcp_client = std::make_unique<TCPClient>(m_io, boost::asio::ip::tcp::resolver(m_io).resolve(ip, port));
	///m_udp_client = std::make_unique<UDPClient>(m_io, boost::asio::ip::udp::resolver(m_io).resolve(ip, port));
	m_thread     = std::thread{ [this]() { m_io.run(); } };
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Client::run()
{
	m_tcp_client->async_connect();

	std::string command;
	while (std::getline(std::cin, command))
		send_command(command);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Client::send_command(std::string_view command)
{
	static auto cmd_fmt{ boost::format{ "%2llu" } };

	std::size_t separator_pos{ command.find_first_of(' ') };
	if (separator_pos == std::string::npos)
		separator_pos = command.length();

	const auto cmd_line{ command.substr(0, separator_pos) };
	      auto args    { command.substr(separator_pos) };
		  if (const auto length = args.length(); length >= CMPROTO::MAX_ARGS_LENGTH)
		  {
			  LOG(warning) << "The command argument is very long. Data clipping";

			  args.remove_suffix(length - CMPROTO::MAX_ARGS_LENGTH);
		  }

	std::unique_ptr<CMPROTO> msg{ std::make_unique<CMPROTO>() };
	msg->set_body_length(CMPROTO::COMMAND_LENGTH + (args.empty() ? 0ull : CMPROTO::SPACE_LENGTH + args.length()));
	if (auto iter = std::find_if(std::begin(COMMAND_PROPERTIES), std::end(COMMAND_PROPERTIES), [&cmd_line](const auto &prop) { return (cmd_line == std::get<1>(prop.command)); }); iter != std::end(COMMAND_PROPERTIES))
	{                                               
		std::string cmd_buff{ boost::str(cmd_fmt % static_cast<std::size_t>(std::get<Commands>(iter->command))) };
		cmd_buff += args;

		// Copy full command 
		std::copy(std::cbegin(cmd_buff), std::cend(cmd_buff), std::begin(msg->get_body()));

		msg->encode_header();

		if (iter->exec_func.index() == 0ull)
			m_tcp_client->write(std::move(msg));
		///else
			///m_udp_client->send(msg);
	}
	else
		LOG(error) << "Wrong Command: '" << command.data() << "'";
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Client::close()
{
	m_tcp_client->close();

	m_thread.join();
}
