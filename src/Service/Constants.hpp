#pragma once

#ifndef __CONSTANTS_H_INCLUDED__
#define __CONSTANTS_H_INCLUDED__

#define TEXTH(str)         (PTCHAR)TEXT(str)
#define TROJAN_APP_NAME    TEXTH("Trojan.exe")

inline static constexpr std::size_t SMALL_BUFFER_LENGTH{ 256 };

inline static constexpr std::string_view SERVER_IP   { "127.0.0.1" };
inline static constexpr std::string_view DEFAULT_PORT{ "20000" };

// Client constants
inline static constexpr std::string_view CLIENT_LOG_FMT_FILENAME{ "client%N.log" };

// Server constants
inline static constexpr std::string_view SERVER_LOG_FMT_FILENAME{ "server%N.log" };

// Injector defines
inline static constexpr std::size_t PATH_LENGTH{ 256 };

// Keylogger defines
#define KEYLOGGER_APP_NAME      TEXT("Keylogger.exe")
#define KEYLOGGER_BUFFER_LENGTH 64
#define KEYBOARD_STATE_SIZE     256

#endif /* __CONSTANTS_H_INCLUDED__ */