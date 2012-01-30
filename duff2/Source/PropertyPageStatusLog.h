#if !defined(AFX_STATUSLOGPROPERTYPAGE_H__16900E0B_BBC5_416D_8846_FB507905FE02__INCLUDED_)
#define AFX_STATUSLOGPROPERTYPAGE_H__16900E0B_BBC5_416D_8846_FB507905FE02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StatusLogPropertyPage.h : header file
//
#include "ResizableLib\ResizablePage.h"

/////////////////////////////////////////////////////////////////////////////
// CStatusLogPropertyPage dialog

class CStatusLogPropertyPage : public CResizablePage
{
	DECLARE_DYNCREATE(CStatusLogPropertyPage)

	friend class CDuffDlg;

// Construction
public:
	CStatusLogPropertyPage();
	~CStatusLogPropertyPage();

private:
	double m_DescriptionColumn;

// Dialog Data
	//{{AFX_DATA(CStatusLogPropertyPage)
	enum { IDD = IDD_STATUSLOG_PAGE };
	CListCtrl	m_StatusLog;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CStatusLogPropertyPage)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


	// Generated message map functions
	//{{AFX_MSG(CStatusLogPropertyPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSaveLog();
	afx_msg void OnClearLog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATUSLOGPROPERTYPAGE_H__16900E0B_BBC5_416D_8846_FB507905FE02__INCLUDED_)
