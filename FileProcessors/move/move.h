// move.h : main header file for the MOVE DLL
//

#if !defined(AFX_MOVE_H__9B941E9D_A41D_4F86_B138_16FD8310C6F8__INCLUDED_)
#define AFX_MOVE_H__9B941E9D_A41D_4F86_B138_16FD8310C6F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMoveApp
// See move.cpp for the implementation of this class
//

class CMoveApp : public CWinApp
{
public:
	CMoveApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMoveApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMoveApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOVE_H__9B941E9D_A41D_4F86_B138_16FD8310C6F8__INCLUDED_)
