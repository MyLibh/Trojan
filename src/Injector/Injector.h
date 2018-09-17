#pragma once

#ifndef __INJECTOR_H_INCLUDED__
#define __INJECTOR_H_INCLUDED__

#include <Windows.h>

#define PATH_LENGTH         256
#define SMALL_BUFFER_LENGTH PATH_LENGTH

DWORD GetProcessID(const PTCHAR process_name);
BOOL FileExist(const PTCHAR filename);
BOOL InjectByName(const PTCHAR process, const PTCHAR dll);
BOOL Inject(DWORD process_id, const PTCHAR path);

BOOL GetProcessList();
BOOL ListProcessModules(DWORD process_id);
BOOL ListProcessThreads(DWORD owner_process_id);

BOOL TraverseHeapList();

VOID PrintError(const PTCHAR msg);

#endif /* __INJECTOR_H_INCLUDED__ */