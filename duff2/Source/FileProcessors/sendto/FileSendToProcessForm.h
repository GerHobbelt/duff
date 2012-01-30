#if !defined(AFX_FILESENDTOPROCESSFORM_H__E815E860_5A50_4B7D_8AA1_3B6A2B92CE4D__INCLUDED_)
#define AFX_FILESENDTOPROCESSFORM_H__E815E860_5A50_4B7D_8AA1_3B6A2B92CE4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileSendToProcessForm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileSendToProcessForm dialog

class CFileSendToProcessForm : public CDialog
{
// Construction
public:
	CFileSendToProcessForm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileSendToProcessForm)
	enum { IDD = IDD_FILE_SENDTO_PROCESS_FORM };
	CEdit	m_ProgramCtrl;
	CEdit	m_ParametersCtrl;
	CString	m_Program;
	CString	m_Parameters;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileSendToProcessForm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileSendToProcessForm)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILESENDTOPROCESSFORM_H__E815E860_5A50_4B7D_8AA1_3B6A2B92CE4D__INCLUDED_)
