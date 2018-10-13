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

#ifndef __DEBUGGER_HPP_INCLUDED__
#define __DEBUGGER_HPP_INCLUDED__

//====================================================================================================================================
//!
//! \brief  Constructs color
//!
//! \param   color       Text color
//! \param   background  Background color
//! \return  Constructed color
//====================================================================================================================================

inline WORD MAKECOLOR(WORD color, WORD background) { return ((background << 4) | color); }

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
//! \brief	 Prints 'warning', using DarkGray color for text and Black for background
//!
//! \param   warning  Text for output
//!
//! \note    If an error occurs, it will be displayed in console(STD_OUTPUT_HANDLE)
//!
//====================================================================================================================================

VOID DebugWarning(CONST PTCHAR warning);

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
//! \brief	Prints the formated boost::system::error_code
//!
//! \param  ec  Name of the function, which failed
//!
//====================================================================================================================================

void PrintBoostError(boost::system::error_code ec);

//====================================================================================================================================
//!
//! \brief	 Clears the console output
//!
//! \note    If an error occurs, it will be displayed in console(STD_OUTPUT_HANDLE)
//!
//====================================================================================================================================

VOID ClearConsole();

#define $i DebugInfo(TEXTH("[I]: ")); 
#define $e DebugError(TEXTH("[E]: "));
#define $w DebugWarning(TEXTH("[W]: "));

#define $info  DebugInfo(TEXTH("[INFO]: ")); 
#define $error DebugError(TEXTH("[ERROR]: "));
#define $warn  DebugWarning(TEXTH("[WARNING]: "));

#ifdef NDEBUG
	#define $I(msg, ...) { $i _tprintf(msg, __VA_ARGS__); }
	#define $E(msg, ...) { $e _tprintf(msg, __VA_ARGS__); }
	#define $W(msg, ...) { $w _tprintf(msg, __VA_ARGS__); }

	#define $INFO(msg, ...)  { $info  _tprintf(msg, __VA_ARGS__); }
	#define $ERROR(msg, ...) { $error _tprintf(msg, __VA_ARGS__); }
	#define $WARN(msg, ...)  { $warn  _tprintf(msg, __VA_ARGS__); }
#else
	#define $I(msg, ...) 
	#define $E(msg, ...) 
	#define $W(msg, ...) 

	#define $INFO(msg, ...)  
	#define $ERROR(msg, ...) 
	#define $WARN(msg, ...)  
#endif /* NDEBUG */

#define TEXTH(msg) (PTCHAR)TEXT(msg)

#endif /* __DEBUGGER_H_INCLUDED__ */