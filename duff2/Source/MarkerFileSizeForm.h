#if !defined(AFX_FILESIZEMARKERFORM_H__BF1CE5B3_0589_4E6F_8071_DE2F4AAD2BD6__INCLUDED_)
#define AFX_FILESIZEMARKERFORM_H__BF1CE5B3_0589_4E6F_8071_DE2F4AAD2BD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileSizeMarkerForm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileSizeMarkerForm dialog

class CFileSizeMarkerForm : public CDialog
{
// Construction
public:
	CFileSizeMarkerForm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileSizeMarkerForm)
	enum { IDD = IDD_FILE_SIZE_MARKER_FORM };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileSizeMarkerForm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileSizeMarkerForm)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILESIZEMARKERFORM_H__BF1CE5B3_0589_4E6F_8071_DE2F4AAD2BD6__INCLUDED_)
