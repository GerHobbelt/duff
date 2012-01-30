// duff.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "duff.h"
#include "duffDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CDuffApp

BEGIN_MESSAGE_MAP(CDuffApp, CWinApp)
	//{{AFX_MSG_MAP(CDuffApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDuffApp construction

CDuffApp::CDuffApp() //: m_Timeout(2002,11,1,0,0,0)
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDuffApp object

CDuffApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDuffApp initialization

BOOL CDuffApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
#if 0
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif
	
	/*
		if (m_Timeout.HasTimedOut())
		{
			AfxMessageBox( StringFromResource(IDS_TIMEOUT_MESSAGE) );
			return FALSE;
		}
	*/
	

	// set the INI profile file name with full path
	free((void*)m_pszProfileName);
	CString Temp (m_pszHelpFilePath);
	Temp = Temp.Left (Temp.GetLength () - 3);
	Temp += _T("dat");
	m_pszProfileName=_tcsdup((const TCHAR *) Temp);
 //

	// load options
 m_DuffOptions.LoadOptions();


	CDuffDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
