#pragma once

#include <WinSock2.h>

class Application
{
	BOOL startSavingThread();

public:
	Application();
	~Application();

	BOOL init();
	VOID run();

private:
	SOCKET m_tcpServer_sock;
};