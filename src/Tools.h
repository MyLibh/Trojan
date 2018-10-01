#pragma once

#ifndef __TOOLS_H_INCLUDED__
#define __TOOLS_H_INCLUDED__

#include <Windows.h>

BOOL FileExist(CONST PTCHAR filename);
BOOL Copy2Sysdir(CONST PTCHAR appname);
BOOL SaveInReg(CONST PTCHAR appname);
VOID StayAlive();
VOID SafeFree(VOID *ptr);

#endif /* __TOOLS_H_INCLUDED__ */