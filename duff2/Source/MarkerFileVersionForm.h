#if !defined(AFX_FILEVERSIONMARKERFORM_H__1F1556A4_1359_4D01_AB22_F2FC8C6DAA5F__INCLUDED_)
#define AFX_FILEVERSIONMARKERFORM_H__1F1556A4_1359_4D01_AB22_F2FC8C6DAA5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileVersionMarkerForm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileVersionMarkerForm dialog

class CFileVersionMarkerForm : public CDialog
{
// Construction
public:
	CFileVersionMarkerForm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileVersionMarkerForm)
	enum { IDD = IDD_FILE_VERSION_MARKER_FORM };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileVersionMarkerForm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileVersionMarkerForm)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEVERSIONMARKERFORM_H__1F1556A4_1359_4D01_AB22_F2FC8C6DAA5F__INCLUDED_)
