#if !defined(AFX_FILEMOVEPROCESSFORM_H__4E73EA14_7849_43F6_88AB_D2A5726B7425__INCLUDED_)
#define AFX_FILEMOVEPROCESSFORM_H__4E73EA14_7849_43F6_88AB_D2A5726B7425__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileMoveProcessForm.h : header file
//

#include "..\..\FilenameEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CFileMoveProcessForm dialog

class CFileMoveProcessForm : public CDialog
{
// Construction
public:
	CFileMoveProcessForm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileMoveProcessForm)
	enum { IDD = IDD_FILE_MOVE_PROCESS_FORM };
	CButton	m_YesToAll;
	CButton	m_MoveReadOnly;
	CFilenameEdit	m_Dir;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileMoveProcessForm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileMoveProcessForm)
	afx_msg void OnBrowse();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEMOVEPROCESSFORM_H__4E73EA14_7849_43F6_88AB_D2A5726B7425__INCLUDED_)
