#include "Injector.h"

#include <tlhelp32.h> 
#include <stdlib.h>   // malloc, free
#include <stdio.h>    // printf
#include <io.h>       // _access

DWORD GetProcessID(const char *process_name)
{
	DWORD process_id = 0;

	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, process_id);
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		printf("Cannot open handle, error: %lu.\n", GetLastError());

		return 0;
	}

	PROCESSENTRY32 pe32 = { sizeof(PROCESSENTRY32) };
	if (!Process32First(hSnapshot, &pe32))
	{
		if (GetLastError() == ERROR_NO_MORE_FILES)
			printf("No processes exist or the snapshot does not contain process information.\n");
		else
			printf("Cannot copy entry of the process list to the buffer, error: %lu.\n", GetLastError());

		if (!CloseHandle(hSnapshot))
			printf("Cannot close the snapshot, error: %lu.\n", GetLastError());

		return 0;
	}

	do
	{
		if (_stricmp(pe32.szExeFile, process_name) == 0)
		{
			process_id = pe32.th32ProcessID;

			break;
		}
	} while (Process32Next(hSnapshot, &pe32));
		
	if(!CloseHandle(hSnapshot))
		printf("Cannot close the snapshot, error: %lu.\n", GetLastError());

	return process_id;
}

BOOL FileExist(const char *filename)
{
	int code = _access(filename, 0); // Checks for existence only - (mode = 0)
	if (code == 0)
		return TRUE;
	else
		switch (errno)
		{
		case EACCES:
			printf("Access denied: the file's permission setting does not allow specified access.\n");
			break;

		case ENOENT: 
			printf("File name or path not found.\n"); 
			break;

		case EINVAL: 
			printf("Invalid parameter.\n"); 
			break;

		default:
			printf("Unknown error.\n");
			break;
		}
	

	return FALSE;
}

BOOL InjectByName(const char *process, const char *dll)
{
	DWORD process_id = 0;
	while (!(process_id = GetProcessID(process)));

	char *path = (char*)malloc(PATH_LENGTH);
	if (!path)
	{
		printf("Cannot allocate memory for dll path.\n");

		return FALSE;
	}

	DWORD path_length = GetFullPathName(dll, PATH_LENGTH, path, NULL);
	if (!path_length)
	{
		printf("Cannot get dll path, error: %lu.\n", GetLastError());
		free(path);

		return FALSE;
	}
	else if (path_length > PATH_LENGTH)
	{
		free(path);

		size_t new_path_length = path_length;
		path = (char*)malloc(new_path_length);

		path_length = GetFullPathName(dll, PATH_LENGTH, path, NULL);
		if (!path_length || path_length > new_path_length)
		{
			printf("Cannot get dll path, error: %lu.\n", GetLastError());
			free(path);

			return FALSE;
		}

	}
	
	if (!FileExist(path))
	{
		printf("Cannot find dll \'%s\'.\n", dll);
		free(path);

		return FALSE;
	}

	if (!Inject(process_id, path))
	{
		printf("Cannot inject dll \'%s\'.\n", path);
		free(path);

		return FALSE;
	}
	free(path);
	
	return TRUE;
}

BOOL Inject(DWORD process_id, const char *path)
{
	if (!process_id)
	{
		printf("Invalid process id: %lu.\n", process_id);

		return FALSE;
	}

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_id);
	if (!hProcess)
	{
		printf("Cannot open process handle, error: %lu.\n", GetLastError());

		return FALSE;
	}

	size_t path_length   = strlen(path);
	LPVOID remote_string = (LPVOID)VirtualAllocEx(hProcess, NULL, path_length, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (!remote_string)
	{
		printf("Cannot allocated region of pages, error: %lu.\n", GetLastError());
		if (!CloseHandle(hProcess))
			printf("Cannot close the process, error: %lu.\n", GetLastError());

		return FALSE;
	}

	if (!WriteProcessMemory(hProcess, remote_string, path, path_length, NULL))
	{
		printf("The requested write operation crosses into an area of the process that is inaccessible, error: %lu.\n", GetLastError());
		if (!CloseHandle(hProcess))
			printf("Cannot close the process, error: %lu.\n", GetLastError());

		return FALSE;
	}

	FARPROC load_lib_add = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
	if (!load_lib_add)
	{
		printf("Cannot export function, error: %lu.\n", GetLastError());
		if (!CloseHandle(hProcess))
			printf("Cannot close the process, error: %lu.\n", GetLastError());

		return FALSE;
	}

	if (!CreateRemoteThread(hProcess, NULL, 0ul, (LPTHREAD_START_ROUTINE)load_lib_add, remote_string, 0ul, 0ul))
	{
		printf("Cannot create remote thread, error: %lu.\n", GetLastError());
		if (!CloseHandle(hProcess))
			printf("Cannot close the process, error: %lu.\n", GetLastError());

		return FALSE;
	}

	if (!CloseHandle(hProcess))
		printf("Cannot close the process, error: %lu.\n", GetLastError());

	return TRUE;
}

BOOL GetProcessList()
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		printf("Cannot open handle, error: %lu.\n", GetLastError());

		return FALSE;
	}

	PROCESSENTRY32 pe32 = { sizeof(PROCESSENTRY32) };
	if (!Process32First(hSnapshot, &pe32))
	{
		if (GetLastError() == ERROR_NO_MORE_FILES)
			printf("No processes exist or the snapshot does not contain process information.\n");
		else
			printf("Cannot copy entry of the process list to the buffer, error: %lu.\n", GetLastError());

		if (!CloseHandle(hSnapshot))
			printf("Cannot close the process, error: %lu.\n", GetLastError());

		return FALSE;
	}

	do
	{
		printf("=====================================================\n");
		printf("PROCESS NAME: %s\n", pe32.szExeFile);
		printf("=====================================================\n");

		hSnapshot = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
		if (!hSnapshot)
		{
			printf("Cannot open process handle, error: %lu.\n", GetLastError());

			return FALSE;
		}
	
		DWORD priority_class = GetPriorityClass(hSnapshot);
		if (!priority_class)
		{
			printf("Cannot get priority class, error: %lu.\n", GetLastError());
			if (!CloseHandle(hSnapshot))
				printf("Cannot close the snapshot, error: %lu.\n", GetLastError());

			return FALSE;
		}

		printf("Process ID        = 0x%08X\n", pe32.th32ProcessID);
		printf("Thread count      = %lu\n",    pe32.cntThreads);
		printf("Parent process ID = 0x%08X\n", pe32.th32ParentProcessID);
		printf("Priority base     = %lu\n",    pe32.pcPriClassBase);
		if (priority_class)
			printf("Priority class    = %lu\n", priority_class);

		ListProcessModules(pe32.th32ProcessID);
		ListProcessThreads(pe32.th32ProcessID);
	} while (Process32Next(hSnapshot, &pe32));

	if (!CloseHandle(hSnapshot))
		printf("Cannot close the snapshot, error: %lu.\n", GetLastError());

	return(TRUE);
}

BOOL ListProcessModules(DWORD process_id)
{
	HANDLE hModule_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, process_id);
	if (hModule_snapshot == INVALID_HANDLE_VALUE)
	{
		printf("Cannot open handle, error: %lu.\n", GetLastError());

		return FALSE;
	}

	MODULEENTRY32 me32 = { sizeof(MODULEENTRY32) };
	if (!Module32First(hModule_snapshot, &me32))
	{
		if (GetLastError() == ERROR_NO_MORE_FILES)
			printf("No modules exist or the snapshot does not contain module information.\n");
		else
			printf("Cannot copy entry of the module list to the buffer, error: %lu.\n", GetLastError());

		if (!CloseHandle(hModule_snapshot))
			printf("Cannot close the process, error: %lu.\n", GetLastError());

		return FALSE;
	}

	do
	{
		printf("MODULE NAME:     %s",     me32.szModule);
		printf("Executable     = %s",     me32.szExePath);
		printf("Process ID     = 0x%08X", me32.th32ProcessID);
		printf("Ref count (g)  = 0x%04X", me32.GlblcntUsage);
		printf("Ref count (p)  = 0x%04X", me32.ProccntUsage);
		printf("Base address   = 0x%08X", (DWORD)me32.modBaseAddr);
		printf("Base size      = %lu",    me32.modBaseSize);

	} while (Module32Next(hModule_snapshot, &me32));

	if (!CloseHandle(hModule_snapshot))
		printf("Cannot close the process, error: %lu.\n", GetLastError());

	return TRUE;
}

BOOL ListProcessThreads(DWORD owner_process_id)
{ 
	HANDLE hThread_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hThread_snapshot == INVALID_HANDLE_VALUE)
	{
		printf("Cannot open handle, error: %lu.\n", GetLastError());

		return FALSE;
	}

	THREADENTRY32 te32 = { sizeof(THREADENTRY32) };
	if (!Thread32First(hThread_snapshot, &te32))
	{
		if (GetLastError() == ERROR_NO_MORE_FILES)
			printf("No threads exist or the snapshot does not contain thread information.\n");
		else
			printf("Cannot copy entry of the thread list to the buffer, error: %lu.\n", GetLastError());

		if (!CloseHandle(hThread_snapshot))
			printf("Cannot close the snapshot, error: %lu.\n", GetLastError());

		return FALSE;
	}

	do
	{
		if (te32.th32OwnerProcessID == owner_process_id)
		{
			printf("THREAD ID      = 0x%08X\n", te32.th32ThreadID);
			printf("Base priority  = %ld\n", te32.tpBasePri);
			printf("Delta priority = %ld\n", te32.tpDeltaPri);
		}
	} while (Thread32Next(hThread_snapshot, &te32));

	if (!CloseHandle(hThread_snapshot))
		printf("Cannot close the snapshot, error: %lu.\n", GetLastError());

	return TRUE;
}

BOOL TraverseHeapList()
{
	HANDLE hHeap_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST, GetCurrentProcessId());
	if (hHeap_snapshot == INVALID_HANDLE_VALUE)
	{
		printf("Cannot open handle, error: %lu.\n", GetLastError());

		return FALSE;
	}

	HEAPLIST32 heap_list = { sizeof(HEAPLIST32) };
	if (Heap32ListFirst(hHeap_snapshot, &heap_list))
	{
		do
		{
			HEAPENTRY32 heap_entry = { sizeof(HEAPENTRY32) };

			if (Heap32First(&heap_entry, GetCurrentProcessId(), heap_list.th32HeapID))
			{
				printf("Heap ID: %d\n", heap_list.th32HeapID);
				do
				{
					printf("\tBlock size: %d\n", heap_entry.dwBlockSize);

					heap_entry.dwSize = sizeof(HEAPENTRY32);
				} while (Heap32Next(&heap_entry));
			}

			heap_list.dwSize = sizeof(HEAPLIST32);
		} while (Heap32ListNext(hHeap_snapshot, &heap_list));
	}
	else
		printf("Cannot list first heap, error: %lu.\n", GetLastError());


	if (!CloseHandle(hHeap_snapshot))
		printf("Cannot close the heap snapshot, error: %lu.\n", GetLastError());

	return TRUE;
}
