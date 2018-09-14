#pragma once

#ifndef __SERVER_H_INCLUDED__
#define __SERVER_H_INCLUDED__

#include <WinSock2.h>

#define MAX_BUFFER_LENGTH 4096
#define CMD_LENGTH        2
#define ARGS_LENGTH       126

#define DEFAULT_PORT      "27015"

typedef enum  
{
	MESSAGE = 'm',
	EXECUTE = 'e'
} Commands;

SOCKET InitServer();
VOID RunServer(SOCKET listen_sock);

#endif /* __SERVER_H_INCLUDED__ */