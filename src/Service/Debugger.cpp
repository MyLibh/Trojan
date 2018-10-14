#include "pch.hpp"

#include "Debugger.hpp"

WORD GetConsoleColor()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE)
	{
		PrintError(TEXTH("GetConsoleScreenBufferInfoEx"), GetLastError());

		return 0;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbf = { 0 };
	if (!GetConsoleScreenBufferInfo(hConsole, &csbf))  //-V2001 https://social.msdn.microsoft.com/Forums/windowsdesktop/en-US/c131afcf-41a8-4e59-93d6-6c9f73dce2e1/getconsolescreenbufferinfoex-failed?forum=windowsgeneraldevelopmentissues
	{
		PrintError(TEXTH("GetConsoleScreenBufferInfoEx"), GetLastError());

		return 0;
	}

	return csbf.wAttributes;
}

WORD SetConsoleColor(WORD color)
{
	WORD old = GetConsoleColor();

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE)
	{
		PrintError(TEXTH("GetConsoleScreenBufferInfoEx"), GetLastError());

		return 0;
	}

	if (!SetConsoleTextAttribute(hConsole, color))
	{
		PrintError(TEXTH("SetConsoleTextAttribute"), GetLastError());

		return 0;
	}

	return old;
}

VOID DebugInfo(const PTCHAR info)
{
	WORD old = SetConsoleColor(MAKECOLOR(LightBlue, Black));

	_tprintf(TEXT("%s"), info);

	SetConsoleColor(old);
}

VOID DebugError(const PTCHAR error)
{
	WORD old = SetConsoleColor(MAKECOLOR(Red, Black));

	_tprintf(TEXT("%s"), error);

	SetConsoleColor(old);
}

VOID DebugWarning(const PTCHAR warning)
{
	WORD old = SetConsoleColor(MAKECOLOR(DarkGray, Black));

	_tprintf(TEXT("%s"), warning);

	SetConsoleColor(old);
}

VOID PrintError(CONST PTCHAR func, INT error)
{
	TCHAR sysmsg[SMALL_BUFFER_LENGTH] = { 0 };
	if (!FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), sysmsg, SMALL_BUFFER_LENGTH, NULL))
	{
		$error _tprintf(TEXT("[ERROR]: FormatMessage failed with 0x%x\n"), GetLastError());

		return;
	}

	PTCHAR p = sysmsg;
	while ((*p > 31) || (*p == 9))
		++p;

	do
	{
		*p-- = 0;
	} while (p >= sysmsg && (*p == '.' || *p < 33));

	$ERROR("\'%s\' failed with error %d (%s)\n", func, error, sysmsg);
}

void PrintBoostError(const boost::system::error_code &ec)
{
	$error std::cerr << "BOOST: " << ec.message() << std::endl;
}
	
VOID ClearConsole()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE)
	{
		PrintError(TEXTH("GetConsoleScreenBufferInfoEx"), GetLastError());

		return ;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi = { 0 };
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) //-V2001 https://social.msdn.microsoft.com/Forums/windowsdesktop/en-US/c131afcf-41a8-4e59-93d6-6c9f73dce2e1/getconsolescreenbufferinfoex-failed?forum=windowsgeneraldevelopmentissues
	{
		PrintError(TEXTH("GetConsoleScreenBufferInfo"), GetLastError());

		return;
	}

	COORD position  = { 0,0 };
	DWORD chars_num = csbi.dwSize.X * csbi.dwSize.Y,
		  written   = 0ul;
	if (!FillConsoleOutputCharacter(hConsole, ' ', chars_num, position, &written))
	{
		PrintError(TEXTH("FillConsoleOutputCharacter"), GetLastError());

		return;
	}

	if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, chars_num, position, &written))
	{
		PrintError(TEXTH("FillConsoleOutputAttribute"), GetLastError());

		return;
	}

	if (!SetConsoleCursorPosition(hConsole, position))
	{
		PrintError(TEXTH("SetConsoleCursorPosition"), GetLastError());

		return;
	}
}

