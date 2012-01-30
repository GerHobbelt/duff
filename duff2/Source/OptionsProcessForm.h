#if !defined(AFX_PROCESSOPTIONSFORM_H__541802A0_EDC1_4086_BB47_2C26B8CCE956__INCLUDED_)
#define AFX_PROCESSOPTIONSFORM_H__541802A0_EDC1_4086_BB47_2C26B8CCE956__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProcessOptionsForm.h : header file
//
#include "DuffOptionsConfigDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CProcessOptionsForm dialog

class CProcessOptionsForm : public CDialog, public CDuffOptionsConfigDlg
{
// Construction
public:
	CProcessOptionsForm(CWnd* pParent = NULL);   // standard constructor


	virtual bool SaveOptions();
	virtual bool LoadOptions();

// Dialog Data
	//{{AFX_DATA(CProcessOptionsForm)
	enum { IDD = IDD_OPTIONS_PROCESSES };
	CButton	m_SetProcessWarning;
	CButton	m_AutoPerformProcesses;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProcessOptionsForm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProcessOptionsForm)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROCESSOPTIONSFORM_H__541802A0_EDC1_4086_BB47_2C26B8CCE956__INCLUDED_)
