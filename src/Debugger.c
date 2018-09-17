#include <tchar.h> // _tprintf

#include "Debugger.h"

WORD GetConsoleColor()
{
	CONSOLE_SCREEN_BUFFER_INFOEX csbfex;
	
	if (GetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), &csbfex))
		_tprintf(TEXT("Failed to get console screen buffer info\n"));

	return csbfex.wAttributes;
}

WORD SetConsoleColor(WORD color)
{
	WORD old = GetConsoleColor();

	if (SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color))
		_tprintf(TEXT("Failed to set console text attribute\n"));

	return old;
}


	

