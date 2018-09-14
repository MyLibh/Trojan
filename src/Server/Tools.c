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
	_tprintf("filepath:%s, sysdir:%s\n", filepath, sysdir); 
	if (!CopyFile(filepath, sysdir, TRUE))
	{
		PrintError(TEXT("CopyFile"), FALSE);

		return FALSE;
	}                        

	return TRUE;
}

VOID PrintError(const PTCHAR msg, INT error)
{
	TCHAR sysmsg[SMALL_BUFFER_LENGTH] = "";
	if(!error)
		error = GetLastError();
	if (!FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), sysmsg, SMALL_BUFFER_LENGTH, NULL))
	{
		printf("[ERROR]: FormatMessage failed with 0x%x\n", GetLastError());

		return;
	}

	PTCHAR p = sysmsg;
	while ((*p > 31) || (*p == 9))
		++p;

	do
	{
		*p-- = 0;
	} while (p >= sysmsg && (*p == '.' || *p < 33));

	printf("[ERROR]: \'%s\' failed with error %lu (%s)\n", msg, error, sysmsg);
}