//====================================================================================================================================
//!
//!	\file    Debugger.h
//!
//! \author  MyLibh
//! \date    23 Sep 2018
//!
//! \brief	 Functions used to improve the output 
//!
//====================================================================================================================================

#ifndef __DEBUGGER_H_INCLUDED__
#define __DEBUGGER_H_INCLUDED__

#include <Windows.h>   

//====================================================================================================================================
//!
//! \brief  Macro, which constructs color
//!
//! \param  color       Text color
//! \param  background  Background color
//!
//====================================================================================================================================

#define MAKECOLOR(color, background) (((WORD)(background) << 4) | (WORD)color)

//====================================================================================================================================
//!
//! \brief  Names for colors
//!
//====================================================================================================================================

typedef enum _Colors
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

//====================================================================================================================================
//!
//! \brief	 Recieves the console text attributes
//!
//! \return  The attributes of the characters written to a screen buffer
//!
//! \note    If an error occurs, it will be displayed in console(STD_OUTPUT_HANDLE)
//!
//====================================================================================================================================

WORD GetConsoleColor();

//====================================================================================================================================
//!
//! \brief	 Sets the console text attributes
//!
//! \param   color  New text attributes
//!
//! \return  Old text attributes
//!
//! \note    If an error occurs, it will be displayed in console(STD_OUTPUT_HANDLE)
//!
//====================================================================================================================================

WORD SetConsoleColor(WORD color);

//====================================================================================================================================
//!
//! \brief	 Prints 'info', using LightBlue color for text and Black for background
//!
//! \param   info  Text for output
//!
//! \note    If an error occurs, it will be displayed in console(STD_OUTPUT_HANDLE)
//!
//====================================================================================================================================

VOID DebugInfo(CONST PTCHAR info);

//====================================================================================================================================
//!
//! \brief	 Prints 'error', using Red color for text and Black for background
//!
//! \param   error  Text for output
//!
//! \note    If an error occurs, it will be displayed in console(STD_OUTPUT_HANDLE)
//!
//====================================================================================================================================

VOID DebugError(CONST PTCHAR error);

//====================================================================================================================================
//!
//! \brief	Prints the formated error("'func' failed with error 'code' ('translated_error')\n")
//!
//! \param  func   Name of the function, which failed
//! \param  error  Error code(Usually 'GetLastError()')
//!
//! \note    If an error occurs, it will be displayed in console(STD_OUTPUT_HANDLE)
//!
//====================================================================================================================================

VOID PrintError(CONST PTCHAR func, INT error);

//====================================================================================================================================
//!
//! \brief	 Clears the console output
//!
//! \note    If an error occurs, it will be displayed in console(STD_OUTPUT_HANDLE)
//!
//====================================================================================================================================

VOID ClearConsole();

//====================================================================================================================================
//!
//! \brief  Short version of macros for outputting info
//!
//====================================================================================================================================

#define $i  DebugInfo(TEXT("[I]: ")); 

//====================================================================================================================================
//!
//! \brief  Short version of macros for outputting error
//!
//====================================================================================================================================

#define $e  DebugError(TEXT("[E]: "));

//====================================================================================================================================
//!
//! \brief  Extended version of macros for outputting info
//!
//====================================================================================================================================

#define $info  DebugInfo(TEXT("[INFO]: ")); 

//====================================================================================================================================
//!
//! \brief  Extended version of macros for outputting error
//!
//====================================================================================================================================

#define $error DebugError(TEXT("[ERROR]: "));

#endif /* __DEBUGGER_H_INCLUDED__ */