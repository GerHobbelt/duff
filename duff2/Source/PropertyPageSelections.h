#if !defined(AFX_SELECTIONSPROPERTYPAGE_H__C8E9123A_F55B_4F76_A1F2_B02FB1D7A9D0__INCLUDED_)
#define AFX_SELECTIONSPROPERTYPAGE_H__C8E9123A_F55B_4F76_A1F2_B02FB1D7A9D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectionsPropertyPage.h : header file
//
#include "ResizableLib\ResizablePage.h"

#include "DuplicateFileFind.h"
#include "DuplicateFileFindConfigurer.h"

#define PROGRESS_TIMER 1

/////////////////////////////////////////////////////////////////////////////
// CMarkersPropertyPage dialog

class CMarkersPropertyPage : public CResizablePage, public CDuplicateFileFindConfigurer
{
	DECLARE_DYNCREATE(CMarkersPropertyPage)

	friend class CDuplicatesPropertyPage;

// Construction
public:
	CMarkersPropertyPage();
	~CMarkersPropertyPage();

	virtual int InitDupeFileFind( CDuplicateFileFind &);
private:
	void UpdateForm();
 static UINT PerformSelectionsThread(LPVOID me);
	UINT PerformSelections();
 CWinThread *m_pWorkerThread;

private:
	CCheckListBox m_SelectionCheckList;

// Dialog Data
	//{{AFX_DATA(CMarkersPropertyPage)
	enum { IDD = IDD_SELECTIONS_PAGE };
	CStatic	m_NoConfigText;
	CEdit	m_SelectionDescription;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMarkersPropertyPage)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

	// Generated message map functions
	//{{AFX_MSG(CMarkersPropertyPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectionsMake();
	afx_msg void OnSelchangeSelectionChecklist();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTIONSPROPERTYPAGE_H__C8E9123A_F55B_4F76_A1F2_B02FB1D7A9D0__INCLUDED_)
