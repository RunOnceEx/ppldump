#ifndef _UTIL_H_
#define _UTIL_H_

DWORD LocateProcess(PCHAR szProcessName);
DWORD LocateThread(HANDLE hDriver, DWORD dwProcId, LPVOID pMemory, LPVOID pParam);

#endif
