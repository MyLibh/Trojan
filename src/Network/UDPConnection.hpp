#pragma once

#ifndef _UDPCONNECTION_HPP_INCLUDED__
#define _UDPCONNECTION_HPP_INCLUDED__ 

#include "INetConnection.hpp"

class IUDPConnection abstract : public INetConnection
{
public:
	virtual BOOL init(CONST std::string &ip, u_short port = DEFAULT_PORT) = 0; 
	virtual BOOL send(CONST std::string &msg)        final override;
	virtual BOOL send(CONST LPBYTE msg, size_t size) final override;
	virtual BOOL recv(std::string &buff)             final override;
};

class UDPClient final : public IUDPConnection
{
public:
	virtual BOOL init(CONST std::string &ip = SERVER_IP, u_short port = DEFAULT_PORT) final override;
};

class UDPServer final : public IUDPConnection
{
public:
	UDPServer();

	virtual BOOL init(CONST std::string &ip = SERVER_IP, u_short port = DEFAULT_PORT) final override;

private:
	SOCKADDR_IN m_serveraddr;
};

#endif /* _UDPCONNECTION_HPP_INCLUDED__ */