#pragma once

class TCPServer;

class Application
{
	BOOL startSavingThread();

public:
	Application();
	~Application();

	BOOL init();
	VOID run();

private:
	TCPServer *m_pTCPServer;
};