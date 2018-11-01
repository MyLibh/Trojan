#pragma once

#ifndef __CLIENT_HPP_INCLUDED__
#define __CLIENT_HPP_INCLUDED__

#include "..\Service\NeedPostInit.hpp"

class TCPClient;
class UDPClient;

class Client : public NeedPostInit
{
public:
	Client() noexcept;
#pragma warning(suppress : 26432)
	// warning C26432: If you define or delete any default operation in the type 'class Client', define or delete them all (c.21).
	~Client() noexcept;

	void init(std::string_view ip, std::string_view port);

	template<typename... Types>
	inline static std::shared_ptr<Client> create(Types... args);

	void run();
	void send_command(std::string_view command);
	void close();

private:
	boost::asio::io_context    m_io;
	std::unique_ptr<TCPClient> m_tcp_client;
	std::unique_ptr<UDPClient> m_udp_client;
	std::thread                m_thread;
};

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template<typename... Types>
std::shared_ptr<Client> Client::create(Types... args)
{
	return NeedPostInit::create<Client, Types...>(args...);
}

#endif /* __CLIENT_HPP_INCLUDED__ */