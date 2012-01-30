#if !defined(AFX_FILEDATEMARKERFORM_H__B16291AC_30C3_4B97_86AB_AA6841E2AE40__INCLUDED_)
#define AFX_FILEDATEMARKERFORM_H__B16291AC_30C3_4B97_86AB_AA6841E2AE40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileDateMarkerForm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileDateMarkerForm dialog

class CFileDateMarkerForm : public CDialog
{
// Construction
public:
	CFileDateMarkerForm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileDateMarkerForm)
	enum { IDD = IDD_FILE_DATE_MARKER_FORM };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileDateMarkerForm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileDateMarkerForm)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEDATEMARKERFORM_H__B16291AC_30C3_4B97_86AB_AA6841E2AE40__INCLUDED_)
