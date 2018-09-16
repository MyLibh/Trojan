#pragma once

#ifndef __TOOLS_H_INCLUDED__
#define __TOOLS_H_INCLUDED__

#include <Windows.h>

BOOL Copy2Sysdir();
// BOOL SaveInReg();

VOID PrintError(const PTCHAR msg, INT error);
//inline VOID PrintError(const PTCHAR msg) { PrintError(msg, 0); }
VOID ClearConsole();

#endif /* __TOOLS_H_INCLUDED__ */