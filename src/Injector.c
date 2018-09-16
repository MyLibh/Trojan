#include "Injector.h"

#include <TlHelp32.h> //
#include <stdlib.h>   // malloc, free
#include <tchar.h>    // _tprintf
#include <io.h>       // _access

DWORD GetProcessID(const PTCHAR process_name)
{
	DWORD  process_id = 0ul;
	HANDLE  hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, process_id);
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		PrintError(TEXT("CreateToolhelp32Snapshot"));

		return 0;
	}

	PROCESSENTRY32 pe32 = { sizeof(PROCESSENTRY32) };
	if (!Process32First(hSnapshot, &pe32))
	{
		PrintError(TEXT("Process32First"));

		if (!CloseHandle(hSnapshot))
			PrintError(TEXT("CloseHandle"));

		return 0;
	}

	do
	{
		if (_tcscmp(pe32.szExeFile, process_name) == 0)
		{
			process_id = pe32.th32ProcessID;

			break;
		}
	} while (Process32Next(hSnapshot, &pe32));
		
	if(!CloseHandle(hSnapshot))
		PrintError(TEXT("CloseHandle"));

	return process_id;
}

BOOL FileExist(const PTCHAR filename)
{
	int code = _taccess(filename, 0); // Checks for existence only - (mode = 0)
	if (code == 0)
		return TRUE;
	else
		switch (errno)
		{
		case EACCES:
			_tprintf(TEXT("Access denied: the file's permission setting does not allow specified access.\n"));
			break;

		case ENOENT: 
			_tprintf(TEXT("File name or path not found.\n"));
			break;

		case EINVAL: 
			_tprintf(TEXT("Invalid parameter.\n"));
			break;

		default:
			_tprintf(TEXT("Unknown error.\n"));
			break;
		}
	

	return FALSE;
}

BOOL InjectByName(const PTCHAR process, const PTCHAR dll)
{
	DWORD process_id = 0;
	while (!(process_id = GetProcessID(process)));

	PTCHAR path = (PTCHAR)malloc(PATH_LENGTH);
	if (!path)
	{
		_tprintf(TEXT("Cannot allocate memory for dll path.\n"));

		return FALSE;
	}

	DWORD path_length = GetFullPathName(dll, PATH_LENGTH, path, NULL);
	if (!path_length)
	{
		PrintError(TEXT("GetFullPathName"));

		return FALSE;
	}
	
	if (!FileExist(path))
	{
		_tprintf(TEXT("Cannot find dll \'%s\'.\n"), dll);
		free(path);

		return FALSE;
	}

	if (!Inject(process_id, path))
	{
		_tprintf(TEXT("Cannot inject dll \'%s\'.\n"), path);
		free(path);

		return FALSE;
	}
	free(path);
	
	return TRUE;
}

BOOL Inject(DWORD process_id, const PTCHAR path)
{
	if (!process_id)
	{
		_tprintf(TEXT("Invalid process id: %lu.\n"), process_id);

		return FALSE;
	}

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_id);
	if (!hProcess)
	{
		PrintError(TEXT("OpenProcess"));

		return FALSE;
	}

	size_t path_length   = _tcslen(path);
	LPVOID remote_string = (LPVOID)VirtualAllocEx(hProcess, NULL, path_length, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (!remote_string)
	{
		PrintError(TEXT("VirtualAllocEx"));
		if (!CloseHandle(hProcess))
			PrintError(TEXT("CloseHandle"));

		return FALSE;
	}

	if (!WriteProcessMemory(hProcess, remote_string, path, path_length, NULL))
	{
		PrintError(TEXT("WriteProcessMemory"));
		if (!CloseHandle(hProcess))
			PrintError(TEXT("CloseHandle"));

		return FALSE;
	}

	FARPROC load_lib_add = GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "LoadLibraryA");
	if (!load_lib_add)
	{
		PrintError(TEXT("GetProcAddress"));
		if (!CloseHandle(hProcess))
			PrintError(TEXT("CloseHandle"));

		return FALSE;
	}

	if (!CreateRemoteThreadEx(hProcess, NULL, 0ul, (LPTHREAD_START_ROUTINE)load_lib_add, remote_string, 0ul, NULL, NULL))
	{
		PrintError(TEXT("CreateRemoteThread"));
		if (!CloseHandle(hProcess))
			PrintError(TEXT("CloseHandle"));

		return FALSE;
	}

	if (!CloseHandle(hProcess))
		PrintError(TEXT("CloseHandle"));

	return TRUE;
}

BOOL GetProcessList()
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		PrintError(TEXT("CreateToolhelp32Snapshot"));

		return FALSE;
	}

	PROCESSENTRY32 pe32 = { sizeof(PROCESSENTRY32) };
	if (!Process32First(hSnapshot, &pe32))
	{
		PrintError(TEXT("Process32First"));
		if (!CloseHandle(hSnapshot))
			PrintError(TEXT("CloseHandle"));

		return FALSE;
	}

	do
	{
		_tprintf(TEXT("=====================================================\n"));
		_tprintf(TEXT("PROCESS NAME: %s\n"), pe32.szExeFile);
		_tprintf(TEXT("=====================================================\n"));

		hSnapshot = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
		if (!hSnapshot)
		{
			PrintError(TEXT("OpenProcess"));

			return FALSE;
		}
	
		DWORD priority_class = GetPriorityClass(hSnapshot);
		if (!priority_class)
		{
			PrintError(TEXT("GetPriorityClass"));
			if (!CloseHandle(hSnapshot))
				PrintError(TEXT("CloseHandle"));

			return FALSE;
		}

		_tprintf(TEXT("Process ID        = 0x%08X\n"), pe32.th32ProcessID);
		_tprintf(TEXT("Thread count      = %lu\n"),    pe32.cntThreads);
		_tprintf(TEXT("Parent process ID = 0x%08X\n"), pe32.th32ParentProcessID);
		_tprintf(TEXT("Priority base     = %ld\n"),    pe32.pcPriClassBase);
		_tprintf(TEXT("Priority class    = %lu\n"),    priority_class);

		ListProcessModules(pe32.th32ProcessID);
		ListProcessThreads(pe32.th32ProcessID);            
	} while (Process32Next(hSnapshot, &pe32));

	if (!CloseHandle(hSnapshot))
		PrintError(TEXT("CloseHandle"));

	return(TRUE);
}

BOOL ListProcessModules(DWORD process_id)
{
	HANDLE hModule_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, process_id);
	if (hModule_snapshot == INVALID_HANDLE_VALUE)
	{
		PrintError(TEXT("CreateToolhelp32Snapshot"));

		return FALSE;
	}

	MODULEENTRY32 me32 = { sizeof(MODULEENTRY32) };
	if (!Module32First(hModule_snapshot, &me32))
	{
		PrintError(TEXT("Module32First"));

		if (!CloseHandle(hModule_snapshot))
			PrintError(TEXT("CloseHandle"));

		return FALSE;
	}

	do
	{
		_tprintf(TEXT("MODULE NAME:     %s"),     me32.szModule);
		_tprintf(TEXT("Executable     = %s"),     me32.szExePath);
		_tprintf(TEXT("Process ID     = 0x%08X"), me32.th32ProcessID);
		_tprintf(TEXT("Ref count (g)  = 0x%04X"), me32.GlblcntUsage);
		_tprintf(TEXT("Ref count (p)  = 0x%04X"), me32.ProccntUsage);
		_tprintf(TEXT("Base address   = 0x%08X"), (DWORD)*me32.modBaseAddr);
		_tprintf(TEXT("Base size      = %lu"),    me32.modBaseSize);

	} while (Module32Next(hModule_snapshot, &me32));

	if (!CloseHandle(hModule_snapshot))
		PrintError(TEXT("CloseHandle"));

	return TRUE;
}

BOOL ListProcessThreads(DWORD owner_process_id)
{ 
	HANDLE hThread_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hThread_snapshot == INVALID_HANDLE_VALUE)
	{
		PrintError(TEXT("CreateToolhelp32Snapshot"));

		return FALSE;
	}

	THREADENTRY32 te32 = { sizeof(THREADENTRY32) };
	if (!Thread32First(hThread_snapshot, &te32))
	{
		PrintError(TEXT("Thread32First"));

		if (!CloseHandle(hThread_snapshot))
			PrintError(TEXT("CloseHandle"));

		return FALSE;
	}

	do
	{
		if (te32.th32OwnerProcessID == owner_process_id)
		{
			_tprintf(TEXT("THREAD ID      = 0x%08X\n"), te32.th32ThreadID);
			_tprintf(TEXT("Base priority  = %ld\n"), te32.tpBasePri);
			_tprintf(TEXT("Delta priority = %ld\n"), te32.tpDeltaPri);
		}
	} while (Thread32Next(hThread_snapshot, &te32));

	if (!CloseHandle(hThread_snapshot))
		PrintError(TEXT("CloseHandle"));

	return TRUE;
}

BOOL TraverseHeapList()
{
	HANDLE hHeap_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST, GetCurrentProcessId());
	if (hHeap_snapshot == INVALID_HANDLE_VALUE)
	{
		_tprintf(TEXT("Cannot open handle, error: %lu.\n"), GetLastError());

		return FALSE;
	}

	HEAPLIST32 heap_list = { sizeof(HEAPLIST32) };
	if (!Heap32ListFirst(hHeap_snapshot, &heap_list))
	{
		PrintError(TEXT("Heap32ListFirst"));
		if (!CloseHandle(hHeap_snapshot))
			PrintError(TEXT("CloseHandle"));

		return FALSE;
	}

	do
	{
		HEAPENTRY32 heap_entry = { sizeof(HEAPENTRY32) };

		if (Heap32First(&heap_entry, GetCurrentProcessId(), heap_list.th32HeapID))
		{
			_tprintf(TEXT("Heap ID: %llu\n"), heap_list.th32HeapID);
			do
			{
				_tprintf(TEXT("\tBlock size: %llu\n"), heap_entry.dwBlockSize);

				heap_entry.dwSize = sizeof(HEAPENTRY32);
			} while (Heap32Next(&heap_entry));
		}

		heap_list.dwSize = sizeof(HEAPLIST32);
	} while (Heap32ListNext(hHeap_snapshot, &heap_list));

	if (!CloseHandle(hHeap_snapshot))
		PrintError(TEXT("CloseHandle"));

	return TRUE;
}

