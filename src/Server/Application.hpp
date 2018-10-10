#pragma once

#ifndef __APLICATION_HPP_INCLUDED__
#define __APLICATION_HPP_INCLUDED__

class TCPServer;

class Application
{
public:
	Application();
	Application(char *argv[]);
	~Application();

	void run();
	void close();

private:
	boost::asio::io_context  m_io;
	TCPServer               *m_server;
	std::thread              m_thread,
                             m_save_thread;
};

#endif /* __APLICATION_HPP_INCLUDED__ */