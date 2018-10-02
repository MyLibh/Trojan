#pragma once

#ifndef __TOOLS_H_INCLUDED__
#define __TOOLS_H_INCLUDED__

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

BOOL FileExist(CONST PTCHAR filename);
BOOL Copy2Sysdir(CONST PTCHAR appname);
BOOL SaveInReg(CONST PTCHAR appname);

VOID StayAlive();

VOID SafeFree(LPVOID ptr);

#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* __TOOLS_H_INCLUDED__ */