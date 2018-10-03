#include "..\pch.h"

#include "TCPConnection.hpp"
#include "..\Debugger.h"

BOOL ITCPConnection::send(CONST std::string &msg)
{
	size_t length = msg.length();
	INT    bytes  = ::send(m_socket, msg.c_str(), static_cast<INT>(length), 0);
	if (bytes == SOCKET_ERROR)
	{
		PrintError(TEXTH("send"), WSAGetLastError());

		return FALSE;
	}
	else if (bytes < length)
	{
		$info _tprintf(TEXTH("Bytes lost:%llu\n"), length - bytes);

		return FALSE;
	}

	return TRUE;
}

BOOL ITCPConnection::send(CONST LPBYTE msg, size_t size)
{
	INT bytes = ::send(m_socket, reinterpret_cast<char*>(msg), static_cast<INT>(size), 0);
	if (bytes == SOCKET_ERROR)
	{
		PrintError(TEXTH("send"), WSAGetLastError());

		return FALSE;
	}
	else if (static_cast<size_t>(bytes) < size)
	{
		$info _tprintf(TEXTH("Bytes lost:%llu\n"), size - static_cast<size_t>(bytes));

		return FALSE;
	}

	return TRUE;
}

BOOL ITCPConnection::recv(std::string &buff)
{
	size_t length = buff.length();
	INT    bytes  = ::recv(m_socket, const_cast<char*>(buff.c_str()), static_cast<INT>(length), 0);
	if (bytes == SOCKET_ERROR)
	{
		PrintError(TEXTH("recv"), WSAGetLastError());

		return FALSE;
	}
	else if (static_cast<size_t>(bytes) < length)
	{
		$info _tprintf(TEXTH("Bytes lost:%llu\n"), length - static_cast<size_t>(bytes));

		return FALSE;
	}

	return TRUE;
}


BOOL TCPClient::init(CONST std::string &ip /* = SERVER_IP */, u_short port /* = DEFAULT_PORT */)
{
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socket == INVALID_SOCKET)
	{
		PrintError(TEXTH("socket"), WSAGetLastError());

		return FALSE;
	}

	m_sockaddr.sin_family      = AF_INET;
	m_sockaddr.sin_port        = htons(port);
	m_sockaddr.sin_addr.s_addr = inet_addr(ip.c_str()); // _WINSOCK_DEPRECATED_NO_WARNINGS

	return TRUE;
}

BOOL TCPClient::connect()
{
	if (::connect(m_socket, reinterpret_cast<LPSOCKADDR>(&m_sockaddr), m_sockaddr_len) == SOCKET_ERROR)
	{
		PrintError(TEXTH("connect"), WSAGetLastError());

		return FALSE;
	}

	return TRUE;
}


TCPServer::TCPServer() : 
	m_clientsocket(INVALID_SOCKET),
	m_clientaddr({ 0 }),
	m_clientaddr_len(sizeof(SOCKADDR_IN))
{
	ZeroMemory(&m_clientaddr, m_clientaddr_len);
}

BOOL TCPServer::init(CONST std::string &ip, u_short port /* = DEFAULT_PORT */)
{
	UNREFERENCED_PARAMETER(ip);

	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socket == INVALID_SOCKET)
	{
		$error PrintError(TEXTH("socket"), WSAGetLastError());

		return FALSE;
	}

	m_sockaddr.sin_family      = AF_INET;
	m_sockaddr.sin_port        = htons(port);
	m_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if (bind(m_socket, reinterpret_cast<LPSOCKADDR>(&m_sockaddr), m_sockaddr_len) == SOCKET_ERROR)
	{
		PrintError(TEXTH("bind"), WSAGetLastError());

		return FALSE;
	}

	if (listen(m_socket, 1) == SOCKET_ERROR)
	{
		PrintError(TEXTH("listen"), WSAGetLastError());

		return FALSE;
	}

	return TRUE;
}

BOOL TCPServer::send(CONST std::string &msg)
{
	size_t length = msg.length();
	INT    bytes = ::send(m_clientsocket, msg.c_str(), static_cast<INT>(length), 0);
	if (bytes == SOCKET_ERROR)
	{
		PrintError(TEXTH("send"), WSAGetLastError());

		return FALSE;
	}
	else if (static_cast<size_t>(bytes) < length)
	{
		$info _tprintf(TEXTH("Bytes lost:%llu\n"), length - static_cast<size_t>(bytes));

		return FALSE;
	}

	return TRUE;
}

BOOL TCPServer::send(CONST LPBYTE msg, size_t size)
{
	INT bytes = ::send(m_clientsocket, reinterpret_cast<char*>(msg), static_cast<INT>(size), 0);
	if (bytes == SOCKET_ERROR)
	{
		PrintError(TEXTH("send"), WSAGetLastError());

		return FALSE;
	}
	else if (static_cast<size_t>(bytes) < size)
	{
		$info _tprintf(TEXTH("Bytes lost:%llu\n"), size - static_cast<size_t>(bytes));

		return FALSE;
	}

	return TRUE;
}

BOOL TCPServer::recv(std::string &buff)
{
	size_t length = buff.length();
	INT    bytes = ::recv(m_clientsocket, const_cast<char*>(buff.c_str()), static_cast<INT>(length), 0);
	if (bytes == SOCKET_ERROR)
	{
		PrintError(TEXTH("recv"), WSAGetLastError());

		return FALSE;
	}
	else if (static_cast<size_t>(bytes) < length)
	{
		$info _tprintf(TEXTH("Bytes lost:%llu\n"), length - static_cast<size_t>(bytes));

		return FALSE;
	}

	return TRUE;
}

BOOL TCPServer::accept()
{
	m_clientsocket = ::accept(m_socket, reinterpret_cast<LPSOCKADDR>(&m_clientaddr), &m_clientaddr_len);
	if (m_clientsocket == INVALID_SOCKET)
	{
		PrintError(TEXTH("accept"), WSAGetLastError());

		return FALSE;
	}

	return TRUE;
}
