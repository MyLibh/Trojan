#pragma once

#ifndef __INJECTOR_H_INCLUDED__
#define __INJECTOR_H_INCLUDED__

#include <Windows.h>

DWORD GetProcessID(CONST PTCHAR process_name);
BOOL  FileExist(CONST PTCHAR filename);
BOOL  InjectByName(CONST PTCHAR process, CONST PTCHAR dll);
BOOL  Inject(DWORD process_id, CONST PTCHAR path);

BOOL GetProcessList();
BOOL ListProcessModules(DWORD process_id);
BOOL ListProcessThreads(DWORD owner_process_id);

BOOL TraverseHeapList();

#endif /* __INJECTOR_H_INCLUDED__ */