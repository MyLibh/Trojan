#pragma once

#ifndef __CLIENTDLL_HPP_INCLUDED__
#define __CLIENTDLL_HPP_INCLUDED__

#define EXTERN_C  extern "C"
#define DLLEXPORT __declspec(dllexport)

class Application;

EXTERN_C DLLEXPORT Application *CtorApplication(const char *cpIP, const char *cpPort);
EXTERN_C DLLEXPORT void         DtorApplication(Application *pApp);
EXTERN_C DLLEXPORT void         SendCommand(Application *pApp, const char *cpCommand);
EXTERN_C DLLEXPORT void         Close(Application *pApp);

#endif /* __CLIENTDLL_HPP_INCLUDED__ */