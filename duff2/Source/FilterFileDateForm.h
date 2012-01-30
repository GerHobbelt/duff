#if !defined(AFX_FILEDATEFILTERFORM_H__7AFE9DEA_ED3F_43DA_BFF5_B18CA5351BE2__INCLUDED_)
#define AFX_FILEDATEFILTERFORM_H__7AFE9DEA_ED3F_43DA_BFF5_B18CA5351BE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileDateFilterForm.h : header file
//

#define DATETIMEFORMAT _T("yyy MMM dd HH:mm:ss")

/////////////////////////////////////////////////////////////////////////////
// CFileDateFilterForm dialog

class CFileDateFilterForm : public CDialog
{
// Construction
public:
	CFileDateFilterForm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileDateFilterForm)
	enum { IDD = IDD_FILE_DATE_FILTER_FORM };
	CButton	m_IgnoreTimeModified;
	CButton	m_IgnoreTimeCreated;
	CButton	m_IgnoreTimeAccessed;
	CComboBox	m_OptionModified;
	CComboBox	m_OptionAccessed;
	CComboBox	m_FilterTypeModified;
	CComboBox	m_FilterTypeAccessed;
	CDateTimeCtrl	m_DateTimeModified2;
	CDateTimeCtrl	m_DateTimeModified1;
	CDateTimeCtrl	m_DateTimeAccessed2;
	CDateTimeCtrl	m_DateTimeAccessed1;
	CComboBox	m_OptionCreated;
	CDateTimeCtrl	m_DateTimeCreated2;
	CDateTimeCtrl	m_DateTimeCreated1;
	CComboBox	m_FilterTypeCreated;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileDateFilterForm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileDateFilterForm)
	afx_msg void OnSelchangeOptionCreated();
	afx_msg void OnSelchangeOptionModified();
	afx_msg void OnSelchangeOptionAccessed();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeFiltertypeCreated();
	afx_msg void OnSelchangeFiltertypeModified();
	afx_msg void OnSelchangeFiltertypeAccessed();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEDATEFILTERFORM_H__7AFE9DEA_ED3F_43DA_BFF5_B18CA5351BE2__INCLUDED_)
