// savelist.h : main header file for the SAVELIST DLL
//

#if !defined(AFX_SAVELIST_H__97EE052F_8346_420F_ACD6_76CB52575656__INCLUDED_)
#define AFX_SAVELIST_H__97EE052F_8346_420F_ACD6_76CB52575656__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSaveListApp
// See savelist.cpp for the implementation of this class
//

class CSaveListApp : public CWinApp
{
public:
	CSaveListApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaveListApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CSaveListApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVELIST_H__97EE052F_8346_420F_ACD6_76CB52575656__INCLUDED_)
