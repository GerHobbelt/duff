#if !defined(AFX_FILENAMELAYERFORM_H__BA1A2FD7_83C1_4BF2_8769_4A7632BF08AA__INCLUDED_)
#define AFX_FILENAMELAYERFORM_H__BA1A2FD7_83C1_4BF2_8769_4A7632BF08AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FilenameLayerForm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFilenameLayerForm dialog

#include "resource.h"

class CFilenameLayerForm : public CDialog
{
// Construction
public:
	CFilenameLayerForm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFilenameLayerForm)
	enum { IDD = IDD_FILENAME_LAYER_FORM };
	CButton	m_CaseSensitive;
	CEdit	m_WordCountCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilenameLayerForm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFilenameLayerForm)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnChangeRadio();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILENAMELAYERFORM_H__BA1A2FD7_83C1_4BF2_8769_4A7632BF08AA__INCLUDED_)
