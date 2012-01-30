#if !defined(AFX_FILEFILTERSPROPERTYPAGE_H__3982FF35_5FBC_49E7_A93C_5D0B643676A9__INCLUDED_)
#define AFX_FILEFILTERSPROPERTYPAGE_H__3982FF35_5FBC_49E7_A93C_5D0B643676A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileFiltersPropertyPage.h : header file
//
#include "ResizableLib\ResizablePage.h"
#include "DuplicateFileFind.h"
#include "DuplicateFileFindConfigurer.h"

/////////////////////////////////////////////////////////////////////////////
// CFileFiltersPropertyPage dialog

class CFileFiltersPropertyPage : public CResizablePage, public CDuplicateFileFindConfigurer
{
	DECLARE_DYNCREATE(CFileFiltersPropertyPage)

	friend class CDuffDlg;

// Construction
public:
	CFileFiltersPropertyPage();
	~CFileFiltersPropertyPage();

private:
	void UpdateForm();
	virtual int  InitDupeFileFind(CDuplicateFileFind &);

private:
	CCheckListBox m_FilterCheckList;

// Dialog Data
	//{{AFX_DATA(CFileFiltersPropertyPage)
	enum { IDD = IDD_FILE_FILTERS_PAGE };
	CStatic	m_NoConfigText;
	CEdit	m_FilterDescription;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFileFiltersPropertyPage)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	// Generated message map functions
	//{{AFX_MSG(CFileFiltersPropertyPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeFilterChecklist();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEFILTERSPROPERTYPAGE_H__3982FF35_5FBC_49E7_A93C_5D0B643676A9__INCLUDED_)
