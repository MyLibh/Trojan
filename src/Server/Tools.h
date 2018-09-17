#pragma once

#ifndef __TOOLS_H_INCLUDED__
#define __TOOLS_H_INCLUDED__

#include <Windows.h>

#define APP_NAME        TEXT("Trojan")
#define APP_NAME4FOLDER TEXT("\\Trojan.exe")

BOOL   FileExist(const PTCHAR filename);
BOOL   Copy2Sysdir();
BOOL   SaveInReg();

VOID PrintError(const PTCHAR msg, INT error);
VOID ClearConsole();

#endif /* __TOOLS_H_INCLUDED__ */