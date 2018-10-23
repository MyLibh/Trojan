#pragma once

#ifndef __APLICATION_HPP_INCLUDED__
#define __APLICATION_HPP_INCLUDED__

class TCPServer;
class UDPServer;

class Application
{
public:
	Application();
	Application(char *argv[]);
	~Application();

	void run();
	void close();

private:
	boost::asio::io_context    m_io;
	std::unique_ptr<TCPServer> m_tcp_server;
	std::unique_ptr<UDPServer> m_udp_server;
	std::thread                m_thread,
                               m_save_thread;
};

#endif /* __APLICATION_HPP_INCLUDED__ */