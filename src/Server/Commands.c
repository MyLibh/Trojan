#include "Commands.h"

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

//TCHAR buf[ARGS_LENGTH + 3] = TEXT(" /c"); // +3 for '/c'
//strcat_s(buf, ARGS_LENGTH + 3, args);
// SHELLEXECUTEINFO shell = { sizeof(SHELLEXECUTEINFO) };
// shell.fMask = SEE_MASK_NOCLOSEPROCESS;
// shell.lpFile = "cmd.exe";
// shell.lpParameters = "ipconfig > a.txt";
// shell.nShow = SW_HIDE;
// ShellExecuteEx(&shell);
// WaitForSingleObject(shell.hProcess, INFINITE);
//ShellExecuteEx(NULL, TEXT("open"), TEXT("cmd.exe"), TEXT("ipconfig > a.out"), NULL, SW_HIDE);

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