// BINDCmd.cpp : implementation file
//

#include <windows.h>
#include "BINDCmd.h"
#include <bind_service.h>
#include <bind_registry.h>
#include <winsvc.h>
#include <stdio.h>

// Time that messages appear on the status bar, in milliseconds
#define MESSAGE_FLASH_TIME 1500

static int numdots = 0;

#define VERSION "1.0.0.0"

// Service status used for host without BIND
#define SERVICE_NOT_INSTALLED             0x00000008

BOOL DoInit()
{
	
	m_svcStatus.dwCurrentState = SERVICE_NOT_INSTALLED;

	m_hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if(!m_hSCManager)
	{
		ShowMessage("Could not open Service Control Manager");
		return FALSE;
	}
	
	m_hBINDSvc = OpenService(m_hSCManager, BIND_SERVICE_NAME, SERVICE_ALL_ACCESS);
	if(!m_hBINDSvc)
	{
		ShowMessage("Could not open BIND Service");
		return FALSE;
	}

	QueryStatus(-1);	// Just get the status
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}


//////////////////////////////////////////////////////////////////////
// Send control codes to the service
void DoStart(char *buf) 
{
	LPTSTR params[32];
	int paramCount = 0;

	//strncpy(params, buf, 31);

	BOOL rc = StartService(m_hBINDSvc, paramCount, (const char **)params);
	if(rc)
		QueryStatus(SERVICE_RUNNING);		// Wait for this status
	else
		ShowErrorMessage("Service start failed: %s");
}

void DoStop() 
{
	BOOL rc = ControlService(m_hBINDSvc, SERVICE_CONTROL_STOP, &m_svcStatus);

	if(rc)
		QueryStatus(SERVICE_STOPPED);		// Wait for this status
	else
		ShowErrorMessage("Service stop failed: %s");
}

void DoReload() 
{
	BOOL rc = ControlService(m_hBINDSvc, SERVICE_CONTROL_RELOAD, &m_svcStatus);
	
	if(rc)
		ShowMessage("Reload signal dispatched");
	else
		ShowErrorMessage("Reload signal failed: %s");
	QueryStatus(SERVICE_RUNNING);
}

void DoDump() 
{
	BOOL rc = ControlService(m_hBINDSvc, SERVICE_CONTROL_DUMPDB, &m_svcStatus);
	
	if(rc)
		ShowMessage("Dump DB signal dispatched");
	else
		ShowErrorMessage("Dump DB signal failed: %s");

}

void DoNoTrace() 
{
	BOOL rc = ControlService(m_hBINDSvc, SERVICE_CONTROL_NOTRACE, &m_svcStatus);
	
	if(rc && !GetLastError())
		ShowMessage("No trace signal dispatched");
	else
		ShowErrorMessage("No trace signal failed: %s");
}

void DoQueryLog() 
{
	BOOL rc = ControlService(m_hBINDSvc, SERVICE_CONTROL_QRYLOG, &m_svcStatus);
	
	if(rc)
		ShowMessage("Query log toggled");
	else
		ShowErrorMessage("Toggle query log signal failed: %s");
}

void DoStats() 
{
	BOOL rc = ControlService(m_hBINDSvc, SERVICE_CONTROL_STATS, &m_svcStatus);
	
	if(rc)
		ShowMessage("Dump stats signal dispatched");
	else
		ShowErrorMessage("Dump stats signal failed: %s");
}

void DoTrace() 
{
	BOOL rc = ControlService(m_hBINDSvc, SERVICE_CONTROL_TRACE, &m_svcStatus);
	
	if(rc)
		ShowMessage("Increment trace signal dispatched");
	else
		ShowErrorMessage("Increment trace signal failed: %s");
}

//////////////////////////////////////////////////////////////////////
// Support functions
char * StatusString(int status)
{
	char *pszStatus;

	switch(status)
	{
		case SERVICE_RUNNING:
			pszStatus = "running";
			break;
		case SERVICE_START_PENDING:
			pszStatus = "starting";
			break;
		case SERVICE_STOP_PENDING:
			pszStatus = "stopping";
			break;
		case SERVICE_NOT_INSTALLED:
			pszStatus = "not installed";
			break;
		default:
			pszStatus = "stopped";
			break;
	}
	return(pszStatus);
}


void QueryLogStatus()
{
	HKEY hKey;
	DWORD dwSize = sizeof(DWORD);
	DWORD dwType; 
	char buf[32];

	if(RegOpenKey(HKEY_LOCAL_MACHINE, BIND_SESSION_SUBKEY, &hKey) != ERROR_SUCCESS)
		return;

	m_qrylog = RegQueryValueEx(hKey, "QueryLog", NULL, &dwType, (LPBYTE)&m_qrylog, &dwSize);
	
	sprintf(buf, "Query Log %s", m_qrylog ? "Off" : "On");
	ShowMessage(buf);
}

void QueryStatus(DWORD wanted)
{
	TCHAR pszStatus[128];
	BOOL rc;

	// We only perform actual updates to the status structure if we are asked
	// or we have a start or stop state pending.
		
	rc = ControlService(m_hBINDSvc, SERVICE_CONTROL_INTERROGATE, &m_svcStatus);
	if(wanted != -1 && rc == 1) {
		memset(pszStatus, 0, 128);
		sprintf(pszStatus, "BIND service is %s", StatusString(m_svcStatus.dwCurrentState));
		numdots = 0;
		printf(pszStatus);

		while(m_svcStatus.dwCurrentState != wanted && rc== 1)
		{
			// Service starting or stopping.  Set a timer to update state automatically
			numdots++;
			printf(".");

			Sleep(1000);
			rc = ControlService(m_hBINDSvc, SERVICE_CONTROL_INTERROGATE, &m_svcStatus);
		}
		printf("\n");
	}
	
	memset(pszStatus, 0, 128);
	sprintf(pszStatus, "BIND service is %s", StatusString(m_svcStatus.dwCurrentState));

	ShowMessage(pszStatus);
}

LPCTSTR GetErrMessage()
{

	memset(m_pszMsgBuf, 0, sizeof(m_pszMsgBuf));
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), 0, m_pszMsgBuf, sizeof(m_pszMsgBuf), NULL);

	return m_pszMsgBuf;
}

void ShowMessage(LPTSTR msg)
{

	printf( "%s\n", msg);
}

void ShowErrorMessage(LPTSTR msg)
{

	printf(msg, GetErrMessage());
}

void Usage()
{
	printf( "Usage: BatchCmd command\n");
	printf( "where command is one of:\n");
	printf( "reload   - reload configuration file\n");
	printf( "start    - start named\n");
	printf( "stop     - stop named\n");
	printf( "stats    - dump statistics to a file\n");
	printf( "trace    - increment trace level\n");
	printf( "notrace  - turn off tracing\n");
	printf( "dump     - dump cache database to a file\n");
	printf( "querylog - toggle query logging\n");
	printf( "\n");
}

int main( int argc, char *argv[] )
{
	int	RequestId = -1;
	BOOL retStat = FALSE;

	// Command Line Sanity Check
	if ( argc < 2)
	{
		Usage();
		return 0;
	}

	/*
	 * Access the Service Manager
	 */
	if(DoInit() == FALSE)
		return -1;

	/* See which one we need to do */

	if ( stricmp( argv[1], "reload") == 0 )
	{
		DoReload();
		RequestId = 0;
	}
	else if ( stricmp( argv[1], "stats") == 0 )
	{
		DoStats();
		RequestId = 1;
	}
	else if ( stricmp( argv[1], "start") == 0 )
	{
		DoStart(argv[2]);
		RequestId = 2;
	}
	else if ( stricmp( argv[1], "stop") == 0 )
	{
		DoStop();
		RequestId = 3;
	}
	else if ( stricmp( argv[1], "dump") == 0 )
	{
		DoDump();
		RequestId = 4;
	}
	else if ( stricmp( argv[1], "trace") == 0 )
	{
		DoTrace();
		RequestId = 5;
	}
	else if ( stricmp( argv[1], "notrace") == 0 )
	{
		DoNoTrace();
		RequestId = 6;
	}
	else if ( stricmp( argv[1], "querylog") == 0 )
	{
		DoQueryLog();
		RequestId = 7;
	}

	return 0;
}