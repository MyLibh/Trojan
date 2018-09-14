#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define SMALL_BUFFER_LENGTH 128
#define DEFAULT_PORT        "27015"

int __cdecl main(int argc, char **argv)
{
	INT     iResult = 0;
	WSADATA wsaData;
	if (iResult = WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		printf("WSAStartup failed with error: %d\n", iResult);

		system("pause");
		return 1;
	}

	struct addrinfo *result = NULL,
		             hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family   = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if (iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result)) 
	{
		printf("getaddrinfo failed with error: %d\n", iResult); 
	
		WSACleanup(); 

		system("pause");
		return 1;
	}

	SOCKET connect_sock = INVALID_SOCKET;
	for (struct addrinfo *ptr = result; ptr; ptr = ptr->ai_next) 
	{	
		if ((connect_sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol)) == INVALID_SOCKET)
		{
			printf("socket failed with error: %ld\n", WSAGetLastError());

			WSACleanup(); 
			
			system("pause");
			return 1;
		}

		if (connect(connect_sock, ptr->ai_addr, (int)ptr->ai_addrlen) == SOCKET_ERROR)
		{
			closesocket(connect_sock);

			connect_sock = INVALID_SOCKET;

			continue;
		}

		break;
	}

	freeaddrinfo(result);

	if (connect_sock == INVALID_SOCKET)
	{
		printf("Unable to connect to server!\n");

		WSACleanup(); 
		
		system("pause");
		return 1;
	}

	printf("Connected\n");

	if(argc < 2)
	{
		char m[SMALL_BUFFER_LENGTH] = "m Hello!!!";
		send(connect_sock, m, SMALL_BUFFER_LENGTH, 0);

		Sleep(1000);

		char t[SMALL_BUFFER_LENGTH] = "e ipconfig > a.txt";
		send(connect_sock, t, SMALL_BUFFER_LENGTH, 0);
	}
	else
	{

	}

	closesocket(connect_sock);
	WSACleanup();

	system("pause");
	return 0;
}
