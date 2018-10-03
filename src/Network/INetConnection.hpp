#pragma once

#ifndef __INETCONNECTION_HPP_INCLUDED__
#define __INETCONNECTION_HPP_INCLUDED__

#include "..\Constants.h"

class INetConnection abstract
{
public:
	INetConnection();
	~INetConnection();

	virtual BOOL init(CONST std::string &ip, u_short port = DEFAULT_PORT) = 0;
	virtual BOOL send(CONST std::string &msg)                             = 0;
	virtual BOOL send(CONST LPBYTE msg, size_t size)                      = 0;
	virtual BOOL recv(std::string &buff)                                  = 0;

protected:
	SOCKET      m_socket;
	SOCKADDR_IN m_sockaddr;
	INT         m_sockaddr_len;
};

#endif /* __INETCONNECTION_HPP_INCLUDED__ */