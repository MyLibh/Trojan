#pragma once

#ifndef __SERVER_H_INCLUDED__
#define __SERVER_H_INCLUDED__

#include <WinSock2.h>

#define MAX_BUFFER_LENGTH 4096
#define CMD_LENGTH        2
#define ARGS_LENGTH       126

typedef struct Server
{
	SOCKET      listen_sock;
	SOCKADDR_IN addr_sock;
} SERVER, *PSERVER;

typedef enum  
{
	MESSAGE = 'm',
	EXECUTE = 'e'
} Commands;

BOOL InitServer(PSERVER server);
VOID RunServer(PSERVER server);

#endif /* __SERVER_H_INCLUDED__ */