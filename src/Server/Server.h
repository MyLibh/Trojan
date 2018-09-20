#pragma once

#ifndef __SERVER_H_INCLUDED__
#define __SERVER_H_INCLUDED__

#include <WinSock2.h>

SOCKET InitTCPServer();
VOID   RunServer(SOCKET listen_sock);

CONST PTCHAR ExecuteCommand(INT code, CONST PTCHAR args);

#endif /* __SERVER_H_INCLUDED__ */