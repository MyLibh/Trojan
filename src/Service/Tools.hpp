#pragma once

#ifndef __TOOLS_HPP_INCLUDED__
#define __TOOLS_HPP_INCLUDED__

BOOL Copy2Sysdir(CONST PTCHAR appname);
BOOL SaveInReg(CONST PTCHAR appname);

VOID StayAlive(CONST PTCHAR appname);

VOID SafeFree(LPVOID ptr);

#endif /* __TOOLS_HPP_INCLUDED__ */