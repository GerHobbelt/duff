#if !defined(AFX_FILESIZEFILTERFORM_H__BA590501_B420_4050_A30A_23B82CAA4CE0__INCLUDED_)
#define AFX_FILESIZEFILTERFORM_H__BA590501_B420_4050_A30A_23B82CAA4CE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileSizeFilterForm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileSizeFilterForm dialog

class CFileSizeFilterForm : public CDialog
{
// Construction
public:
	CFileSizeFilterForm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileSizeFilterForm)
	enum { IDD = IDD_FILE_SIZE_FILTER_FORM };
	CEdit	m_Value2Control;
	CEdit	m_Value1Control;
	CComboBox	m_FilterTypeControl;
	int		m_FilterType;
	DWORD	m_Value1;
	DWORD	m_Value2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileSizeFilterForm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileSizeFilterForm)
	afx_msg void OnEditchangeFilterType();
	afx_msg void OnSelchangeFilterType();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILESIZEFILTERFORM_H__BA590501_B420_4050_A30A_23B82CAA4CE0__INCLUDED_)
