#ifndef _MLWRFOX_H_
#define _MLWRFOX_H_

#define IOCTL_REG 0x80002010
#define IOCTL_LEAK 0x8000204C
#define IOCTL_THRD 0x80002084

BOOL RegisterProcess(HANDLE hDriver, PDWORD UserPid);
BOOL AcquireHandle(HANDLE hDriver, PDWORD UserPid, PHANDLE OutHandle);
BOOL AcquireThread(HANDLE hDriver, PDWORD UserThrd, PHANDLE OutHandle);
#endif
