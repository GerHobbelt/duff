#if !defined(AFX_FILEDELETEPROCESSFORM_H__EE5548A5_A30B_45FB_B925_1AF6D27B6236__INCLUDED_)
#define AFX_FILEDELETEPROCESSFORM_H__EE5548A5_A30B_45FB_B925_1AF6D27B6236__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileDeleteProcessForm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileDeleteProcessForm dialog

class CFileDeleteProcessForm : public CDialog
{
// Construction
public:
	CFileDeleteProcessForm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileDeleteProcessForm)
	enum { IDD = IDD_FILE_DELETE_PROCESS_FORM };
	CButton	m_YesToAll;
	CButton	m_DeleteReadOnly;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileDeleteProcessForm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileDeleteProcessForm)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEDELETEPROCESSFORM_H__EE5548A5_A30B_45FB_B925_1AF6D27B6236__INCLUDED_)
