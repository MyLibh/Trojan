#pragma once

#ifndef __DEBUGGER_H_INCLUDED__
#define __DEBUGGER_H_INCLUDED__

#include <Windows.h>   

typedef enum  
{
	Black        = 0x00,
	Blue         = 0x01,
	Green        = 0x02,
	Cyan         = 0x03,
	Red          = 0x04,
	Magenta      = 0x05,
	Brown        = 0x06,
	LightGray    = 0x07,
	DarkGray     = 0x08,
	LightBlue    = 0x09,
	LightGreen   = 0x0A,
	LightCyan    = 0x0B,
	LightRed     = 0x0C,
	LightMagenta = 0x0D,
	Yellow       = 0x0E,
	White        = 0x0F
} Colors;

#define MAKECOLOR(color, background) (((WORD)(background) << 4) | (WORD)color)

WORD GetConsoleColor();
WORD SetConsoleColor(WORD color);

#define $i { WORD old = SetConsoleColor(LightBlue); _tprintf(TEXT("[I] ")); SetConsoleColor(old); }
#define $e { WORD old = SetConsoleColor(      Red); _tprintf(TEXT("[E] ")); SetConsoleColor(old); }

#define $info  { WORD old = SetConsoleColor(LightBlue); _tprintf(TEXT("[INFO] ")); SetConsoleColor(old); }
#define $error { WORD old = SetConsoleColor(      Red); _tprintf(TEXT("[ERROR] ")); SetConsoleColor(old); }

#endif /* __DEBUGGER_H_INCLUDED__ */