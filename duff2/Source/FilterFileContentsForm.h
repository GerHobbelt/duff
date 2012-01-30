#if !defined(AFX_FILECONTENTSFILTERFORM_H__CA275A3D_594E_4E69_BFA8_4C47B3894C72__INCLUDED_)
#define AFX_FILECONTENTSFILTERFORM_H__CA275A3D_594E_4E69_BFA8_4C47B3894C72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileContentsFilterForm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileContentsFilterForm dialog

class CFileContentsFilterForm : public CDialog
{
// Construction
public:
	CFileContentsFilterForm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileContentsFilterForm)
	enum { IDD = IDD_FILE_CONTENTS_FILTER_FORM };
	CEdit	m_ContentString;
	CButton	m_CaseSensitive;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileContentsFilterForm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileContentsFilterForm)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILECONTENTSFILTERFORM_H__CA275A3D_594E_4E69_BFA8_4C47B3894C72__INCLUDED_)
