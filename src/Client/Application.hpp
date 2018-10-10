#pragma once

#ifndef __APPLICATION_HPP_INCLUDED__
#define __APPLICATION_HPP_INCLUDED__

class TCPClient;
class UDPParticipiant;

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
	TCPClient               *m_tcp_client;
	UDPParticipiant         *m_udp_participiant;
	std::thread              m_thread;
};

#endif /* __APPLICATION_HPP_INCLUDED__ */