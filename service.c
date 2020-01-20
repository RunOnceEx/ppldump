#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "service.h"

BOOL LoadDriver(
  PCHAR szDriverPath
)
{
  SC_HANDLE ServiceMan = NULL;
  SC_HANDLE ServicePtr = NULL;
  BOOL      boolRetVal = FALSE;

  ServiceMan = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
  if ( ServiceMan != NULL ) {
    ServicePtr = CreateServiceA(ServiceMan, SVC_NAME, SVC_NAME,
		    SERVICE_START | DELETE | SERVICE_STOP,
		    SERVICE_KERNEL_DRIVER, SERVICE_DEMAND_START,
		    SERVICE_ERROR_IGNORE, szDriverPath, NULL,
		    NULL, NULL, NULL, NULL);
    if ( ServicePtr != NULL ) {
	StartService(ServicePtr, 0, NULL);
	CloseServiceHandle(ServicePtr);
	boolRetVal = TRUE;
    };
    CloseServiceHandle(ServiceMan);
  };
  return boolRetVal;
};

BOOL UnloadDriver(
  VOID
)
{
  SC_HANDLE      ServiceMan  = NULL;
  SC_HANDLE      ServicePtr  = NULL;
  SERVICE_STATUS ServiceStat =  { 0 };
  BOOL           boolRetVal  = FALSE;

  ServiceMan = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
  if ( ServiceMan != NULL ) {
    ServicePtr = OpenServiceA(ServiceMan, 
		    SVC_NAME, SERVICE_STOP | DELETE);
    if ( ServicePtr != NULL ) {
      ControlService
      (
        ServicePtr, 
	SERVICE_CONTROL_STOP, 
	&ServiceStat
      );
      DeleteService(ServicePtr);
      CloseServiceHandle(ServicePtr);
      boolRetVal = TRUE;
    };
    CloseServiceHandle(ServiceMan);
  };
  return boolRetVal;
};
