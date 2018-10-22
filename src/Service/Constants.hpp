#pragma once

#ifndef __CONSTANTS_H_INCLUDED__
#define __CONSTANTS_H_INCLUDED__

#include <tchar.h>

#define TEXTH(str) (PTCHAR)TEXT(str)

#define SMALL_BUFFER_LENGTH     256

#define SERVER_IP          "127.0.0.1" 
#define DEFAULT_PORT       "20000"

#define TROJAN_APP_NAME    TEXTH("Trojan.exe")

// Commands defines

#define TASK_SUCCESSP       TEXTH("Success")
#define TASK_SUCCESSW       L"Success"
#define TASK_SUCCESSA        "Success"
#define TASK_SUCCESS_LENGTH 7

#define TASK_FAILUREP       TEXTH("Failure")
#define TASK_FAILUREW       L"Failure"
#define TASK_FAILUREA        "Failure"
#define TASK_FAILURE_LENGTH 7

#define UNDEFINEDP          TEXTH("Undefined")
#define UNDEFINEDW          L"Undefined"
#define UNDEFINEDA           "Undefined"
#define UNDEFINED_LENGTH    9

// Injector defines
#define PATH_LENGTH 256

// Keylogger defines
#define KEYLOGGER_APP_NAME      TEXT("Keylogger.exe")
#define KEYLOGGER_BUFFER_LENGTH 64
#define KEYBOARD_STATE_SIZE     256

#endif /* __CONSTANTS_H_INCLUDED__ */