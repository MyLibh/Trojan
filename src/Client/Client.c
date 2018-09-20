#include "..\Constants.h"
#include "..\Debugger.h"

// #include <ws2tcpip.h> // InetPton
#include <stdlib.h>   // system
#include <stdio.h>

#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")
// #pragma comment (lib, "AdvApi32.lib")

int __cdecl main(int argc, char **argv)
{
	WSADATA wsaData; 
	INT     iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		$e _tprintf(TEXT("WSAStartup failed with error: %d\n"), iResult);

		system("pause");
		return 1;
	}
	$i _tprintf(TEXT("Startup finished\n"));

	SOCKET connect_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect_sock == INVALID_SOCKET)
	{
		$e _tprintf(TEXT("socket failed with error: %ld\n"), WSAGetLastError());

		WSACleanup();

		system("pause");
		return 1;
	}
	$i _tprintf(TEXT("Connecting...\n"));

	SOCKADDR_IN connect_sockaddr;
	ZeroMemory(&connect_sockaddr, sizeof(SOCKADDR_IN));
	connect_sockaddr.sin_family      = AF_INET;
	connect_sockaddr.sin_addr.s_addr = inet_addr(argc > 1 ? argv[1] : SERVER_IP); // _WINSOCK_DEPRECATED_NO_WARNINGS
	connect_sockaddr.sin_port        = htons(DEFAULT_PORT);
	//InetPton(AF_INET, TEXT("127.0.0.1"), &connect_sockaddr.sin_addr.s_addr); 
	if (connect(connect_sock, (LPSOCKADDR)&connect_sockaddr, sizeof(struct sockaddr)) == SOCKET_ERROR)
	{
		$e _tprintf(TEXT("connect failed with error: %ld\n"), WSAGetLastError());

		closesocket(connect_sock);
		WSACleanup();

		system("pause");
		return 1;
	}
	$i _tprintf(TEXT("Connected\n"));

	if (argc > 2) // _CRT_SECURE_NO_WARNINGS
	{
		char message[TCP_MESSAGE_LENGTH] = { 0 };
		strcpy(message, argv[2]);
		strcat(strcat(message, " "), argv[3]);
		INT bytes = send(connect_sock, message, TCP_MESSAGE_LENGTH, 0);
		$i _tprintf(TEXT("%d bytes sent1\n"), bytes);
	}
	else 
	{
		char message[TCP_MESSAGE_LENGTH] = "05 netstat /release";
		INT bytes = send(connect_sock, message, TCP_MESSAGE_LENGTH, 0);
		$i _tprintf(TEXT("%d bytes sent2\n"), bytes);
	}

	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		POINT cursor = { 0 };
		GetCursorPos(&cursor);
		$i _tprintf(TEXT("%d %d\n"), cursor.x, cursor.y);
		char message[TCP_MESSAGE_LENGTH] = { 0 };
		sprintf(message, "06 %d %d", cursor.x, cursor.y);
		INT bytes = send(connect_sock, message, TCP_MESSAGE_LENGTH, 0);
	}

	char result[TCP_MESSAGE_LENGTH] = { 0 };
	recv(connect_sock, result, TCP_MESSAGE_LENGTH, 0);
	$i _tprintf(TEXT("Result: %hs\n"), result);

	closesocket(connect_sock);
	WSACleanup();

	system("pause");
	return 0;
}
