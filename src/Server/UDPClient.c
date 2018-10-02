#include "pch.h" 

#include "UDPClient.h"
#include "..\Debugger.h"
#include "..\Constants.h"

/*SOCKET InitUDPCLient()
{
	WSADATA wsaData;
	INT     iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		$error _tprintf(TEXT("WSAStartup failed with error: %d\n"), iResult);

		return INVALID_SOCKET;
	}
	$info _tprintf(TEXT("Startup finished\n"));

	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listen_sock == INVALID_SOCKET)
	{
		PrintError(TEXT("socket"), WSAGetLastError());

		WSACleanup();

		return INVALID_SOCKET;
	}

	SOCKADDR_IN addr_sock;
	addr_sock.sin_family = AF_INET;
	addr_sock.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_sock.sin_port = htons(DEFAULT_PORT);
	if (bind(listen_sock, (LPSOCKADDR)&addr_sock, sizeof(addr_sock)) == SOCKET_ERROR)
	{
		PrintError(TEXT("bind"), WSAGetLastError());

		closesocket(listen_sock);
		WSACleanup();

		return INVALID_SOCKET;
	}
	$info _tprintf(TEXT("Binding socket finished\n"));

	if (listen(listen_sock, 1) == SOCKET_ERROR)
	{
		PrintError(TEXT("listen"), WSAGetLastError());

		closesocket(listen_sock);
		WSACleanup();

		return INVALID_SOCKET;
	}
	$info _tprintf(TEXT("Socket started to listen\n"));

	return listen_sock;

	return INVALID_SOCKET;
}

BOOL SendUDPPacket()
{
	return 0;
}*/
