#if !defined(AFX_DEBUGPAGE_H__5DEF0776_F7F4_4E28_8E50_03C4C2EBD634__INCLUDED_)
#define AFX_DEBUGPAGE_H__5DEF0776_F7F4_4E28_8E50_03C4C2EBD634__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DebugPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDebugPage dialog

class CDebugPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CDebugPage)

// Construction
public:
	CDebugPage();
	~CDebugPage();

// Dialog Data
	//{{AFX_DATA(CDebugPage)
	enum { IDD = IDD_DEBUG_PAGE };
	CStatic	m_FileInfoCount;
	CListBox	m_Files;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDebugPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDebugPage)
	afx_msg void OnReadFiles();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEBUGPAGE_H__5DEF0776_F7F4_4E28_8E50_03C4C2EBD634__INCLUDED_)
