#include "..\pch.h"

#include "INetConnection.hpp"
#include "..\Debugger.h"

INetConnection::INetConnection() :
	m_socket(INVALID_SOCKET),
	m_sockaddr({ 0 }),
	m_sockaddr_len(sizeof(SOCKADDR_IN))
{
	ZeroMemory(&m_sockaddr, m_sockaddr_len);
}

INetConnection::~INetConnection()
{
	if (closesocket(m_socket) != 0)
		PrintError(TEXTH("closesocket"), WSAGetLastError());
}
