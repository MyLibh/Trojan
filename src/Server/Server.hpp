#pragma once

#ifndef __APLICATION_HPP_INCLUDED__
#define __APLICATION_HPP_INCLUDED__

#include "..\Service\NeedPostInit.hpp"

class TCPServer;
class UDPServer;

class Server : public NeedPostInit
{
public:
	Server() noexcept;
	~Server() noexcept;

	void init();
	void init(std::string_view port);

	template<typename... Args>
	inline static std::shared_ptr<Server> create(Args... args);

	void run();
	void close();

private:
	boost::asio::io_context    m_io;
	std::unique_ptr<TCPServer> m_tcp_server;
	std::unique_ptr<UDPServer> m_udp_server;
	std::thread                m_thread,
                               m_save_thread;
};

template<typename... Args>
std::shared_ptr<Server> Server::create(Args... args)
{
	return NeedPostInit::create<Server, Args...>(args...);
}

#endif /* __APLICATION_HPP_INCLUDED__ */