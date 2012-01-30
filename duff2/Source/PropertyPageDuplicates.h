#if !defined(AFX_DUPLICATESPROPERTYPAGE_H__6F9583FE_44A0_49AB_B808_4ECCBCEB5E90__INCLUDED_)
#define AFX_DUPLICATESPROPERTYPAGE_H__6F9583FE_44A0_49AB_B808_4ECCBCEB5E90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DuplicatesPropertyPage.h : header file
//
#include "ResizableLib\ResizablePage.h"
#include "FileInfo.h"
#include "DuffObject.h"

#include "DuplicateListCtrl.h"
#include "DupeFindDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CDuplicatesPropertyPage dialog

class CDuplicatesPropertyPage : public CResizablePage, protected CDuffObject
{
	DECLARE_DYNCREATE(CDuplicatesPropertyPage)

	friend class CDuffDlg;
 friend class CProcessesPropertyPage;
 friend class CMarkersPropertyPage;
 friend class CDupeFindDlg;

public:
	void UpdateListMarks();
	ULONGLONG GetNumFiles();
	void AddItem(CFileInfo*);
	CDuplicatesPropertyPage();
	~CDuplicatesPropertyPage();

// const unsigned long & GetTotalFilesCounter() const { return m_TotalFilesCounter; }

private:
//	void         UpdateTotalInfo();
 virtual void LoadSettings();
	virtual void SaveSettings();
//	void         UpdateListInfo();
// CDupeFindDlg m_DupeFindDlg;

private:

	// Dialog Data
	//{{AFX_DATA(CDuplicatesPropertyPage)
	enum { IDD = IDD_DUPLICATES_PAGE };
	CDuplicateListCtrl	m_DupeList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDuplicatesPropertyPage)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	
	// Generated message map functions
	//{{AFX_MSG(CDuplicatesPropertyPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	//void DoFind();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DUPLICATESPROPERTYPAGE_H__6F9583FE_44A0_49AB_B808_4ECCBCEB5E90__INCLUDED_)
