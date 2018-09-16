#include <tchar.h>

#include "Tools.h"

#define SMALL_BUFFER_LENGTH 256

BOOL Copy2Sysdir()
{
	TCHAR filepath[SMALL_BUFFER_LENGTH] = { 0 };
	if (!GetModuleFileName(GetModuleHandle(NULL), filepath, SMALL_BUFFER_LENGTH))
	{
		PrintError(TEXT("GetModuleFileName"), FALSE);

		return FALSE;
	}

	TCHAR sysdir[SMALL_BUFFER_LENGTH] = { 0 };
	if (!GetSystemDirectory(sysdir, SMALL_BUFFER_LENGTH))
	{
		PrintError(TEXT("GetSystemDirectory"), FALSE);

		return FALSE;
	}

	_tprintf(TEXT("filepath:%s, sysdir:%s\n"), filepath, sysdir);
	if (!CopyFile(filepath, sysdir, TRUE))
	{
		PrintError(TEXT("CopyFile"), FALSE);

		return FALSE;
	}                        

	return TRUE;
}

VOID PrintError(const PTCHAR msg, INT error)
{
	if(!error)
		error = GetLastError();

	TCHAR sysmsg[SMALL_BUFFER_LENGTH] = { 0 };
	if (!FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), sysmsg, SMALL_BUFFER_LENGTH, NULL))
	{
		_tprintf(TEXT("[ERROR]: FormatMessage failed with 0x%x\n"), GetLastError());

		return;
	}

	PTCHAR p = sysmsg;
	while ((*p > 31) || (*p == 9))
		++p;

	do
	{
		*p-- = 0;
	} while (p >= sysmsg && (*p == '.' || *p < 33));

	_tprintf(TEXT("[ERROR]: \'%s\' failed with error %lu (%s)\n"), msg, error, sysmsg);
}

VOID ClearConsole()
{
	HANDLE                     hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO     csbi = { 0 };
	COORD                      position = { 0,0 };
	if (GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		DWORD chars_num = csbi.dwSize.X * csbi.dwSize.Y,
			    written = 0ul;
		FillConsoleOutputCharacter(hConsole, ' ', chars_num, position, &written);
		FillConsoleOutputAttribute(hConsole, csbi.wAttributes, chars_num, position, &written);
	}

	SetConsoleCursorPosition(hConsole, position);
}