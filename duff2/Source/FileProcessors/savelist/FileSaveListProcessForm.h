#if !defined(AFX_FILESAVELISTPROCESSFORM_H__6FC20607_4804_4DA7_BBF6_4E1223313115__INCLUDED_)
#define AFX_FILESAVELISTPROCESSFORM_H__6FC20607_4804_4DA7_BBF6_4E1223313115__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileSaveListProcessForm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileSaveListProcessForm dialog

class CFileSaveListProcessForm : public CDialog
{
// Construction
public:
	CFileSaveListProcessForm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileSaveListProcessForm)
	enum { IDD = IDD_FILE_SAVELIST_PROCESS_FORM };
	CButton	m_NewLine;
	CEdit	m_LineFormat;
	CEdit	m_Filename;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileSaveListProcessForm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileSaveListProcessForm)
	afx_msg void OnBrowse();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILESAVELISTPROCESSFORM_H__6FC20607_4804_4DA7_BBF6_4E1223313115__INCLUDED_)
