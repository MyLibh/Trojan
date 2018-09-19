#pragma once

#ifndef __SERVER_H_INCLUDED__
#define __SERVER_H_INCLUDED__

#include <WinSock2.h>

#define CMD_LENGTH     2
#define ARGS_LENGTH    126
#define MESSAGE_LENGTH 128

#define DEFAULT_PORT 20000

SOCKET InitTCPServer();
VOID RunServer(SOCKET listen_sock);
CONST PTCHAR ExecuteCommand(INT code, CONST PTCHAR args);

#endif /* __SERVER_H_INCLUDED__ */