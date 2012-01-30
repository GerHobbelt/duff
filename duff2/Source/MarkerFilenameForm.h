#if !defined(AFX_FILENAMESELECTIONFORM_H__D3540509_2326_4D06_B0ED_4409B53AB9A1__INCLUDED_)
#define AFX_FILENAMESELECTIONFORM_H__D3540509_2326_4D06_B0ED_4409B53AB9A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FilenameSelectionForm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFilenameMarkerForm dialog

class CFilenameMarkerForm : public CDialog
{
// Construction
public:
	CFilenameMarkerForm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFilenameMarkerForm)
	enum { IDD = IDD_FILENAME_SELECTION_FORM };
	CButton	m_CaseSensitive;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilenameMarkerForm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFilenameMarkerForm)
	virtual BOOL OnInitDialog();
	afx_msg void OnLongest();
	afx_msg void OnContain();
	afx_msg void OnLowercase();
	afx_msg void OnShortest();
	afx_msg void OnDontcontain();
	afx_msg void OnUppercase();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILENAMESELECTIONFORM_H__D3540509_2326_4D06_B0ED_4409B53AB9A1__INCLUDED_)
