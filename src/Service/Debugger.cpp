// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "pch.hpp"

#include "Debugger.hpp"
#include "Constants.hpp"

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
	const WORD old = GetConsoleColor();

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

void DebugInfo(const PTCHAR info)
{
	const WORD old = SetConsoleColor(MAKECOLOR(Colors::LightBlue, Colors::Black));

	_tprintf(TEXT("%s"), info);

	SetConsoleColor(old);
}

void DebugError(const PTCHAR error)
{
	const WORD old = SetConsoleColor(MAKECOLOR(Colors::Red, Colors::Black));

	_tprintf(TEXT("%s"), error);

	SetConsoleColor(old);
}

void DebugWarning(const PTCHAR warning)
{
	const WORD old = SetConsoleColor(MAKECOLOR(Colors::DarkGray, Colors::Black));

	_tprintf(TEXT("%s"), warning);

	SetConsoleColor(old);
}

void PrintError(CONST PTCHAR func, INT error)
{
	TCHAR sysmsg[SMALL_BUFFER_LENGTH]{ };
	
	[[gsl::suppress(26485)]] // Expression 'sysmsg': No array to pointer decay (bounds.3).
	if (!FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), sysmsg, SMALL_BUFFER_LENGTH, nullptr))
	{
		$error _tprintf(TEXT("[ERROR]: FormatMessage failed with 0x%x\n"), GetLastError());

		return;
	}

	const gsl::span<TCHAR> span(sysmsg);
	auto end{ std::find_if_not(std::execution::par_unseq, std::begin(span), std::end(span), [](auto &&c) { return ((c > 31) || (c == 9)); }) };
#pragma warning(suppress : 26486)
	// warning C26486: Don't pass a pointer that may be invalid to a function(lifetime.1).
	if (end == std::end(span))
		end = std::begin(span);

#pragma warning(suppress : 26486)
	// warning C26486: Don't pass a pointer that may be invalid to a function(lifetime.1).
	auto begin{ std::find_if_not(std::execution::par_unseq, std::reverse_iterator(end), std::rend(span), [](auto &&c) { return ((c == '.') || (c < 33)); }) };
	if (begin == std::rend(span))
		begin = std::reverse_iterator(end);

	std::for_each(std::execution::par_unseq, begin.base(), end, [](auto &&c) { c = 0; });

	$ERROR("\'%s\' failed with error %d (%s)\n", func, error, span.data());
}

void PrintBoostError(const boost::system::error_code &ec)
{
	$error std::cerr << "(BOOST): " << ec.message() << std::endl;
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
	const DWORD chars_num = csbi.dwSize.X * csbi.dwSize.Y;
		  DWORD written   = 0ul;
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

