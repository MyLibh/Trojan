#include "Injector.h" 
#include "..\Tools.h"
#include "..\Debugger.h"
#include "..\Constants.h"

#include <TlHelp32.h> 
#include <stdlib.h>   // malloc, free
#include <tchar.h>    // _taccess, _tprintfá _tcscmp

DWORD GetProcessID(CONST PTCHAR process_name) //-V2009
{
	DWORD  process_id = 0ul;
	HANDLE hSnapshot  = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, process_id);
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		PrintError(TEXT("CreateToolhelp32Snapshot"), GetLastError());

		return 0;
	}

	PROCESSENTRY32 pe32 = { sizeof(PROCESSENTRY32) };
	if (!Process32First(hSnapshot, &pe32))
	{
		PrintError(TEXT("Process32First"), GetLastError());

		if (!CloseHandle(hSnapshot))
			PrintError(TEXT("CloseHandle"), GetLastError());

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
		PrintError(TEXT("CloseHandle"), GetLastError());

	return process_id;
}

BOOL FileExist(CONST PTCHAR filename) //-V2009
{
	int code = _taccess(filename, 0); // Checks for existence only - (mode = 0)
	if (code == 0)
		return TRUE;
	else
		switch (errno)
		{
		case EACCES:
			$error _tprintf(TEXT("Access denied: the file's permission setting does not allow specified access.\n"));
			break;

		case ENOENT: 
			$error _tprintf(TEXT("File name or path not found.\n"));
			break;

		case EINVAL: 
			$error _tprintf(TEXT("Invalid parameter.\n"));
			break;

		default:
			$error _tprintf(TEXT("Unknown error.\n"));
			break;
		}
	
	return FALSE;
}

BOOL InjectByName(CONST PTCHAR process, CONST PTCHAR dll)
{
	DWORD process_id = 0ul;
	while (!(process_id = GetProcessID(process)));

	PTCHAR path = (PTCHAR)malloc((size_t)PATH_LENGTH);
	if (!path)
	{
		$error _tprintf(TEXT("Cannot allocate memory for dll path.\n"));

		return FALSE;
	}

	DWORD path_length = GetFullPathName(dll, PATH_LENGTH, path, NULL);
	if (!path_length)
	{
		PrintError(TEXT("GetFullPathName"), GetLastError());
		free(path);

		return FALSE;
	}
	
	if (!FileExist(path))
	{
		$error _tprintf(TEXT("Cannot find dll \'%s\'.\n"), dll);
		free(path);

		return FALSE;
	}

	if (!Inject(process_id, path))
	{
		$error _tprintf(TEXT("Cannot inject dll \'%s\'.\n"), path);
		free(path);

		return FALSE;
	}

	free(path);
	
	return TRUE;
}

BOOL Inject(DWORD process_id, CONST PTCHAR path) //-V2009
{
	if (!process_id)
	{
		$error _tprintf(TEXT("Invalid process id: %lu.\n"), process_id);

		return FALSE;
	}

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_id);
	if (!hProcess)
	{
		PrintError(TEXT("OpenProcess"), GetLastError());

		return FALSE;
	}

	size_t path_length   = _tcslen(path);
	LPVOID remote_string = (LPVOID)VirtualAllocEx(hProcess, NULL, path_length, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (!remote_string)
	{
		PrintError(TEXT("VirtualAllocEx"), GetLastError());
		if (!CloseHandle(hProcess))
			PrintError(TEXT("CloseHandle"), GetLastError());

		return FALSE;
	}

	if (!WriteProcessMemory(hProcess, remote_string, path, path_length, NULL))
	{
		PrintError(TEXT("WriteProcessMemory"), GetLastError());
		if (!CloseHandle(hProcess))
			PrintError(TEXT("CloseHandle"), GetLastError());

		return FALSE;
	}

	HMODULE hModule = NULL;
	if (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, TEXT("kernel32.dll"), &hModule))
	{
		PrintError(TEXT("GetModuleHandleEx"), GetLastError());

		return FALSE;
	}

	FARPROC load_lib_add = GetProcAddress(hModule, "LoadLibraryA");
	if (!load_lib_add)
	{
		PrintError(TEXT("GetProcAddress"), GetLastError());
		if (!CloseHandle(hProcess))
			PrintError(TEXT("CloseHandle"), GetLastError());

		return FALSE;
	}

	if (!CreateRemoteThreadEx(hProcess, NULL, 0ul, (LPTHREAD_START_ROUTINE)load_lib_add, remote_string, 0ul, NULL, NULL))
	{
		PrintError(TEXT("CreateRemoteThread"), GetLastError());
		if (!CloseHandle(hProcess))
			PrintError(TEXT("CloseHandle"), GetLastError());

		return FALSE;
	}

	if (!CloseHandle(hProcess))
		PrintError(TEXT("CloseHandle"), GetLastError());

	return TRUE;
}

BOOL GetProcessList()
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		PrintError(TEXT("CreateToolhelp32Snapshot"), GetLastError());

		return FALSE;
	}

	PROCESSENTRY32 pe32 = { sizeof(PROCESSENTRY32) };
	if (!Process32First(hSnapshot, &pe32))
	{
		PrintError(TEXT("Process32First"), GetLastError());
		if (!CloseHandle(hSnapshot))
			PrintError(TEXT("CloseHandle"), GetLastError());

		return FALSE;
	}

	do
	{
		$i _tprintf(TEXT("=====================================================\n"));
		$i _tprintf(TEXT("PROCESS NAME: %s\n"), pe32.szExeFile);
		$i _tprintf(TEXT("=====================================================\n"));

		hSnapshot = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
		if (!hSnapshot)
		{
			PrintError(TEXT("OpenProcess"), GetLastError());

			return FALSE;
		}
	
		DWORD priority_class = GetPriorityClass(hSnapshot);
		if (!priority_class)
		{
			PrintError(TEXT("GetPriorityClass"), GetLastError());
			if (!CloseHandle(hSnapshot))
				PrintError(TEXT("CloseHandle"), GetLastError());

			return FALSE;
		}

		$i _tprintf(TEXT("Process ID        = 0x%08X\n"), pe32.th32ProcessID);
		$i _tprintf(TEXT("Thread count      = %lu\n"),    pe32.cntThreads);
		$i _tprintf(TEXT("Parent process ID = 0x%08X\n"), pe32.th32ParentProcessID);
		$i _tprintf(TEXT("Priority base     = %ld\n"),    pe32.pcPriClassBase);
		$i _tprintf(TEXT("Priority class    = %lu\n"),    priority_class);

		ListProcessModules(pe32.th32ProcessID);
		ListProcessThreads(pe32.th32ProcessID);            
	} while (Process32Next(hSnapshot, &pe32));

	if (!CloseHandle(hSnapshot))
		PrintError(TEXT("CloseHandle"), GetLastError());

	return TRUE;
}

BOOL ListProcessModules(DWORD process_id)
{
	HANDLE hModule_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, process_id);
	if (hModule_snapshot == INVALID_HANDLE_VALUE)
	{
		PrintError(TEXT("CreateToolhelp32Snapshot"), GetLastError());

		return FALSE;
	}

	MODULEENTRY32 me32 = { sizeof(MODULEENTRY32) };
	if (!Module32First(hModule_snapshot, &me32))
	{
		PrintError(TEXT("Module32First"), GetLastError());

		if (!CloseHandle(hModule_snapshot))
			PrintError(TEXT("CloseHandle"), GetLastError());

		return FALSE;
	}

	do
	{
		$i _tprintf(TEXT("MODULE NAME:     %s"),     me32.szModule);
		$i _tprintf(TEXT("Executable     = %s"),     me32.szExePath);
		$i _tprintf(TEXT("Process ID     = 0x%08X"), me32.th32ProcessID);
		$i _tprintf(TEXT("Ref count (g)  = 0x%04X"), me32.GlblcntUsage);
		$i _tprintf(TEXT("Ref count (p)  = 0x%04X"), me32.ProccntUsage);
		$i _tprintf(TEXT("Base address   = 0x%08X"), (DWORD)*me32.modBaseAddr);
		$i _tprintf(TEXT("Base size      = %lu"),    me32.modBaseSize);

	} while (Module32Next(hModule_snapshot, &me32));

	if (!CloseHandle(hModule_snapshot))
		PrintError(TEXT("CloseHandle"), GetLastError());

	return TRUE;
}

BOOL ListProcessThreads(DWORD owner_process_id)
{ 
	HANDLE hThread_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hThread_snapshot == INVALID_HANDLE_VALUE)
	{
		PrintError(TEXT("CreateToolhelp32Snapshot"), GetLastError());

		return FALSE;
	}

	THREADENTRY32 te32 = { sizeof(THREADENTRY32) };
	if (!Thread32First(hThread_snapshot, &te32))
	{
		PrintError(TEXT("Thread32First"), GetLastError());

		if (!CloseHandle(hThread_snapshot))
			PrintError(TEXT("CloseHandle"), GetLastError());

		return FALSE;
	}

	do
	{
		if (te32.th32OwnerProcessID == owner_process_id)
		{
			$i _tprintf(TEXT("THREAD ID      = 0x%08X\n"), te32.th32ThreadID);
			$i _tprintf(TEXT("Base priority  = %ld\n"), te32.tpBasePri);
			$i _tprintf(TEXT("Delta priority = %ld\n"), te32.tpDeltaPri);
		}
	} while (Thread32Next(hThread_snapshot, &te32));

	if (!CloseHandle(hThread_snapshot))
		PrintError(TEXT("CloseHandle"), GetLastError());

	return TRUE;
}

BOOL TraverseHeapList()
{
	HANDLE hHeap_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST, GetCurrentProcessId());
	if (hHeap_snapshot == INVALID_HANDLE_VALUE)
	{
		PrintError(TEXT("CreateToolhelp32Snapshot"), GetLastError());

		return FALSE;
	}

	HEAPLIST32 heap_list = { sizeof(HEAPLIST32) };
	if (!Heap32ListFirst(hHeap_snapshot, &heap_list))
	{
		PrintError(TEXT("Heap32ListFirst"), GetLastError());
		if (!CloseHandle(hHeap_snapshot))
			PrintError(TEXT("CloseHandle"), GetLastError());

		return FALSE;
	}

	do
	{
		HEAPENTRY32 heap_entry = { sizeof(HEAPENTRY32) };
		if (Heap32First(&heap_entry, GetCurrentProcessId(), heap_list.th32HeapID))
		{
			$i _tprintf(TEXT("Heap ID: %llu\n"), heap_list.th32HeapID);
			do
			{
				$i _tprintf(TEXT("\tBlock size: %llu\n"), heap_entry.dwBlockSize);

				heap_entry.dwSize = sizeof(HEAPENTRY32);
			} while (Heap32Next(&heap_entry));
		}

		heap_list.dwSize = sizeof(HEAPLIST32);
	} while (Heap32ListNext(hHeap_snapshot, &heap_list));

	if (!CloseHandle(hHeap_snapshot))
		PrintError(TEXT("CloseHandle"), GetLastError());

	return TRUE;
}



