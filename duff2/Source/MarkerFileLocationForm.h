#if !defined(AFX_FILELOCATIONMARKERFORM_H__EDDDC4CE_68BB_4BCA_AE70_2A7B47E75270__INCLUDED_)
#define AFX_FILELOCATIONMARKERFORM_H__EDDDC4CE_68BB_4BCA_AE70_2A7B47E75270__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileLocationMarkerForm.h : header file
//

#include "FilenameEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CFileLocationMarkerForm dialog

class CFileLocationMarkerForm : public CDialog
{
// Construction
public:
	CFileLocationMarkerForm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileLocationMarkerForm)
	enum { IDD = IDD_FILE_LOCATION_MARKER_FORM };
	CFilenameEdit	m_Path;
	CButton	m_SubDirs;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileLocationMarkerForm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileLocationMarkerForm)
	virtual BOOL OnInitDialog();
	afx_msg void OnBrowse();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILELOCATIONMARKERFORM_H__EDDDC4CE_68BB_4BCA_AE70_2A7B47E75270__INCLUDED_)
