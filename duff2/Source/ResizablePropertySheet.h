#if !defined(AFX_MYPROPERTYSHEET_H__C36CB51E_E1F4_42DD_B4ED_1CB4D398DCE1__INCLUDED_)
#define AFX_MYPROPERTYSHEET_H__C36CB51E_E1F4_42DD_B4ED_1CB4D398DCE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyPropertySheet.h : header file
//

#include "ResizableLib\ResizableSheet.h"

/////////////////////////////////////////////////////////////////////////////
// CResizablePropertySheet

class CResizablePropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CResizablePropertySheet)

// Construction
public:
	CResizablePropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CResizablePropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
 CResizablePropertySheet(CWnd* pWndParent = NULL);
void  Resize();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResizablePropertySheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CResizablePropertySheet();

	// Generated message map functions
protected:
	CRect m_rectPage;
	//{{AFX_MSG(CResizablePropertySheet)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPROPERTYSHEET_H__C36CB51E_E1F4_42DD_B4ED_1CB4D398DCE1__INCLUDED_)
