#ifndef ABOUT_DLG_23532
#define ABOUT_DLG_23532


#include "resource.h"
#include "hyperlink.h"
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CStatic	m_Copyright;
	CListCtrl	m_PluginInformation;
	CStatic	m_LicenseType;
	CHyperLink	m_Email;
	CStatic	m_Version;
	CStatic	m_CompiledDate;
	CHyperLink	m_HyperLink;
	CHyperLink	m_VersionInfo;
	CHyperLink	m_SizeLib;
	CHyperLink	m_HomePage;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnIconlogo();
	afx_msg void OnDblclkPluginInformation(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#endif
