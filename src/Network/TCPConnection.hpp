#pragma once

#ifndef __TCPCONNECTION_HPP_INCLUDED__
#define __TCPCONNECTION_HPP_INCLUDED__

#include "INetConnection.hpp"

class ITCPConnection abstract : public INetConnection
{
public:
	virtual BOOL init(CONST std::string &ip, u_short port = DEFAULT_PORT) = 0;
	virtual BOOL send(CONST std::string &msg)        override;
	virtual BOOL send(CONST LPBYTE msg, size_t size) override;
	virtual BOOL recv(std::string &buff)             override;
};

class TCPClient final : public ITCPConnection
{
public:
	virtual BOOL init(CONST std::string &ip = SERVER_IP, u_short port = DEFAULT_PORT) final override;
	        BOOL connect();
};

class TCPServer final : public ITCPConnection
{
public:
	TCPServer();

	virtual BOOL init(CONST std::string &ip = SERVER_IP, u_short port = DEFAULT_PORT) final override;
	virtual BOOL send(CONST std::string &msg)                                         final override;
	virtual BOOL send(CONST LPBYTE msg, size_t size)                                  final override;
	virtual BOOL recv(std::string &buff)                                              final override;
			BOOL accept();
			BOOL close_client_socket();
private:
	SOCKET      m_clientsocket;
	SOCKADDR_IN m_clientaddr;
	INT         m_clientaddr_len;
};

#endif /* __TCPCONNECTION_HPP_INCLUDED__ */