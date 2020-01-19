/*
 * Utilities for locating arbitary
 * processes, and loading the driver
 * into kernel space.
*/
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>

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
