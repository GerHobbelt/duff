// duff.h : main header file for the DUFF application
//

#if !defined(AFX_DUFF_H__835EF06C_F40A_4B18_9883_139BEF8EDCE7__INCLUDED_)
#define AFX_DUFF_H__835EF06C_F40A_4B18_9883_139BEF8EDCE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "TimeOut.h"
#include "DuffOptions.h"

/////////////////////////////////////////////////////////////////////////////
// CDuffApp:
// See duff.cpp for the implementation of this class
//

class CDuffApp : public CWinApp
{
public:
	CDuffApp();

//	CTimeOut     m_Timeout;
	CDuffOptions m_DuffOptions;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDuffApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDuffApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DUFF_H__835EF06C_F40A_4B18_9883_139BEF8EDCE7__INCLUDED_)
