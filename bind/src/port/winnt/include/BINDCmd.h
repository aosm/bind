// BINDCtrlDlg.h : header file
//

#include <winsvc.h>


HANDLE m_hSCManager;
HANDLE m_hBINDSvc;
SERVICE_STATUS m_svcStatus;
char m_pszMsgBuf[128];

DWORD m_qrylog;

LPCTSTR GetErrMessage();
char * StatusString(int status);
void ShowMessage(LPTSTR msg);
void ShowErrorMessage(LPTSTR msg);
void QueryLogStatus();
void QueryStatus(DWORD wanted = -1);	//Default no-wait required
