
#ifndef _WINAPI_H
#define _WINAPI_H

typedef HANDLE(WINAPI * GetCurrentProcess_t)();

typedef DWORD(WINAPI * GetCurrentProcessId_t)();

typedef HMODULE(WINAPI * LoadLibraryA_t)(
	LPCSTR lpLibFileName
);

typedef FARPROC(WINAPI * GetProcAddress_t)(
	HMODULE hModule,
	LPCSTR lpProcName
);

typedef BOOL(WINAPI * CloseHandle_t)(
	HANDLE hHandle
);

typedef HANDLE(WINAPI * CreateFileA_t)(
	LPCSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwSharedMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile
);

typedef BOOL (*MiniDumpWriteDump_t)(
	HANDLE hProcess,
	DWORD ProcessId,
	HANDLE hFile,
	MINIDUMP_TYPE DumpType,
	PVOID CallBack,
	PVOID CallBack2,
	PVOID CallBack3
);

#endif
