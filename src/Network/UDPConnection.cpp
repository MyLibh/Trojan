#include "..\pch.h" 

#include "UDPConnection.hpp"
#include "..\Debugger.h"

BOOL IUDPConnection::send(CONST std::string &msg)
{
	size_t length = msg.length();
	INT    bytes = sendto(m_socket, msg.c_str(), static_cast<INT>(length), 0, reinterpret_cast<LPSOCKADDR>(&m_sockaddr), m_sockaddr_len);
	if (bytes == SOCKET_ERROR)
	{
		$error PrintError(TEXTH("sendto"), WSAGetLastError());

		return FALSE;
	}
	else if (static_cast<size_t>(bytes) < length)
	{
		$info _tprintf(TEXTH("Bytes lost:%llu\n"), length - static_cast<size_t>(bytes));

		return FALSE;
	}

	return TRUE;
}

BOOL IUDPConnection::send(CONST LPBYTE msg, size_t size)
{
	INT bytes = sendto(m_socket, reinterpret_cast<char*>(msg), static_cast<INT>(size), 0, reinterpret_cast<LPSOCKADDR>(&m_sockaddr), m_sockaddr_len);
	if (bytes == SOCKET_ERROR)
	{
		$error PrintError(TEXTH("sendto"), WSAGetLastError());

		return FALSE;
	}
	else if (static_cast<size_t>(bytes) < size)
	{
		$info _tprintf(TEXTH("Bytes lost:%llu\n"), size - static_cast<size_t>(bytes));

		return FALSE;
	}

	return TRUE;
}

BOOL IUDPConnection::recv(std::string &buff)
{
	size_t length = buff.length();
	INT    bytes = recvfrom(m_socket, const_cast<char*>(buff.c_str()), static_cast<INT>(length), 0, reinterpret_cast<LPSOCKADDR>(&m_sockaddr), &m_sockaddr_len);
	if (bytes == SOCKET_ERROR)
	{
		$error PrintError(TEXTH("recvfrom"), WSAGetLastError());

		return FALSE;
	}
	else if (bytes < length)
	{
		$info _tprintf(TEXTH("Bytes lost:%llu\n"), length - static_cast<size_t>(bytes));

		return FALSE;
	}

	return TRUE;
}


BOOL UDPClient::init(CONST std::string &ip /* = SERVER_IP */, u_short port /* = DEFAULT_PORT */)
{
	m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_socket == SOCKET_ERROR)
	{
		$error PrintError(TEXTH("socket"), WSAGetLastError());

		return FALSE;
	}

	m_sockaddr.sin_family      = AF_INET;
	m_sockaddr.sin_port        = htons(port);
	m_sockaddr.sin_addr.s_addr = inet_addr(ip.c_str()); // _WINSOCK_DEPRECATED_NO_WARNINGS

	return TRUE;
}


UDPServer::UDPServer() :
	IUDPConnection(),
	m_serveraddr({ 0 })
{ 
	ZeroMemory(&m_serveraddr, sizeof(m_serveraddr));
}

BOOL UDPServer::init(CONST std::string & ip, u_short port /* = DEFAULT_PORT */)
{
	UNREFERENCED_PARAMETER(ip);

	m_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_socket == INVALID_SOCKET)
	{
		$error PrintError(TEXTH("socket"), WSAGetLastError());

		return FALSE;
	}
	
	m_serveraddr.sin_family      = AF_INET;
	m_serveraddr.sin_port        = htons(port);
	m_serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if (bind(m_socket, reinterpret_cast<LPSOCKADDR>(&m_serveraddr), sizeof(m_serveraddr)) == SOCKET_ERROR)
	{
		$error PrintError(TEXTH("bind"), WSAGetLastError());

		return FALSE;
	}

	return TRUE;
}

