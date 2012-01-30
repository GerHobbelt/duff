#if !defined(AFX_MARKEROPTIONSFORM_H__5B62319E_8640_48BB_9B3A_AEDFA313C00E__INCLUDED_)
#define AFX_MARKEROPTIONSFORM_H__5B62319E_8640_48BB_9B3A_AEDFA313C00E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MarkerOptionsForm.h : header file
//

#include "DuffOptionsConfigDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CMarkerOptionsForm dialog

class CMarkerOptionsForm : public CDialog, public CDuffOptionsConfigDlg
{
// Construction
public:
	CMarkerOptionsForm(CWnd* pParent = NULL);   // standard constructor

	virtual bool SaveOptions();
	virtual bool LoadOptions();

	// Dialog Data
	//{{AFX_DATA(CMarkerOptionsForm)
	enum { IDD = IDD_MARKER_OPTIONS_FORM };
	CButton	m_MarkAtLeastOne;
	CButton	m_ClearMarks;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMarkerOptionsForm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMarkerOptionsForm)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MARKEROPTIONSFORM_H__5B62319E_8640_48BB_9B3A_AEDFA313C00E__INCLUDED_)
