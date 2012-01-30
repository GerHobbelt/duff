// sendto.h : main header file for the SENDTO DLL
//

#if !defined(AFX_SENDTO_H__A83732BE_B97F_4C49_A671_55B4645A2BC7__INCLUDED_)
#define AFX_SENDTO_H__A83732BE_B97F_4C49_A671_55B4645A2BC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSendtoApp
// See sendto.cpp for the implementation of this class
//

class CSendtoApp : public CWinApp
{
public:
	CSendtoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendtoApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CSendtoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDTO_H__A83732BE_B97F_4C49_A671_55B4645A2BC7__INCLUDED_)
