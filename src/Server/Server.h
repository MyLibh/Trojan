#pragma once

#ifndef __SERVER_H_INCLUDED__
#define __SERVER_H_INCLUDED__

#ifdef __cplusplus
extern "C" 
{
#endif /* __cplusplus */

SOCKET InitTCPServer();
VOID   RunServer(SOCKET listen_sock);

#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

CONST PTCHAR ExecuteCommand(INT code, CONST PTCHAR args);

#endif /* __SERVER_H_INCLUDED__ */