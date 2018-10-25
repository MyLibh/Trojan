#pragma once

#ifndef __APPLICATION_HPP_INCLUDED__
#define __APPLICATION_HPP_INCLUDED__

class TCPClient;
class UDPClient;

class Application : private boost::noncopyable
{
public:
	Application() noexcept;
	Application(char *argv[]);
	Application(std::string_view ip, std::string_view port);
	~Application();

	void run();
	void send_command(std::string_view command);
	void close();

private:
	boost::asio::io_context    m_io;
	std::unique_ptr<TCPClient> m_tcp_client;
	std::unique_ptr<UDPClient> m_udp_client;
	std::thread                m_thread;
};

#endif /* __APPLICATION_HPP_INCLUDED__ */