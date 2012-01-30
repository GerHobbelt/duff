#if !defined(AFX_PROCESSESPROPERTYPAGE_H__84B67E93_A455_4445_9E9E_09986D05EE2F__INCLUDED_)
#define AFX_PROCESSESPROPERTYPAGE_H__84B67E93_A455_4445_9E9E_09986D05EE2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProcessesPropertyPage.h : header file
//
#include "ResizableLib\ResizablePage.h"
#include "Processor.h"
#include "DuplicateFileFind.h"
#include "DufFPlugin.h"
#include "DuplicateFileFindConfigurer.h"

/////////////////////////////////////////////////////////////////////////////
// CProcessesPropertyPage dialog

class CProcessesPropertyPage : public CResizablePage, public CDuplicateFileFindConfigurer
{
	DECLARE_DYNCREATE(CProcessesPropertyPage)

	friend class CDuffDlg;

// Construction
public:
	void AddPlugin(CDuffPlugin *);
	virtual int InitDupeFileFind( CDuplicateFileFind &);
	CProcessesPropertyPage();
	~CProcessesPropertyPage();

private:
	CCheckListBox m_ProcessCheckList;

	void UpdateForm();

 static UINT PerformProcessesThread(LPVOID me);
	UINT PerformProcesses();
 CWinThread *m_pWorkerThread;

	// Dialog Data
	//{{AFX_DATA(CProcessesPropertyPage)
	enum { IDD = IDD_PROCESSES_PAGE };
	CStatic	m_NoConfigText;
	CEdit	m_ProcessDescription;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CProcessesPropertyPage)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


	// Generated message map functions
	//{{AFX_MSG(CProcessesPropertyPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPerform();
	afx_msg void OnSelchangeProcessChecklist();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void AddProcessor(HINSTANCE hInstance, CFileProcessor*);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROCESSESPROPERTYPAGE_H__84B67E93_A455_4445_9E9E_09986D05EE2F__INCLUDED_)
