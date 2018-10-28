#pragma once

#ifndef __APPLICATION_HPP_INCLUDED__
#define __APPLICATION_HPP_INCLUDED__

#include "..\Service\NeedPostInit.hpp"

class TCPClient;
class UDPClient;

class Application : public NeedPostInit
{
public:
	Application() noexcept;
	~Application();

	void init();
	void init(std::string_view ip, std::string_view port);

	template<typename... Args>
	inline static std::shared_ptr<Application> create(Args... args);

	void run();
	void send_command(std::string_view command);
	void close();

private:
	boost::asio::io_context    m_io;
	std::unique_ptr<TCPClient> m_tcp_client;
	std::unique_ptr<UDPClient> m_udp_client;
	std::thread                m_thread;
};

template<typename... Args>
std::shared_ptr<Application> Application::create(Args... args)
{
	return NeedPostInit::create<Application, Args...>(args...);
}

#endif /* __APPLICATION_HPP_INCLUDED__ */