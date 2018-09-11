#ifndef INJECTOR_H_INCLUDED
#define INJECTOR_H_INCLUDED

#include <Windows.h>

static const size_t PATH_LENGTH = 255;

DWORD GetProcessID(const char *process_name);
BOOL FileExist(const char *filename);
BOOL InjectByName(const char *process, const char *dll);
BOOL Inject(DWORD process_id, const char *path);

BOOL GetProcessList();
BOOL ListProcessModules(DWORD process_id);
BOOL ListProcessThreads(DWORD owner_process_id);

BOOL TraverseHeapList();

#endif /* INJECTOR_H_INCLUDED */