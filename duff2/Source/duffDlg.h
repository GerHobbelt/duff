// duffDlg.h : header file
//

#if !defined(AFX_DUFFDLG_H__DD0D3E95_0F0A_473E_8CF5_EBC454DE9E75__INCLUDED_)
#define AFX_DUFFDLG_H__DD0D3E95_0F0A_473E_8CF5_EBC454DE9E75__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "ResizableLib\ResizableDialog.h"
#include "ResizablePropertySheet.h"
#include "DuffPluginManager.h"

#include "PropertyPageDebug.h"
#include "PropertyPageLayers.h"
#include "PropertyPageDirectories.h"
#include "PropertyPageDuplicates.h"
#include "PropertyPageProcesses.h"
#include "PropertyPageStatusLog.h"
#include "PropertyPageSelections.h"
#include "PropertyPageOptions.h"
#include "PropertyPageFilters.h"
#include "ProgressCtrl64.h"


/////////////////////////////////////////////////////////////////////////////
// CDuffDlg dialog
//class CDuplicateFileFind;

class CDuffDlg : public CResizableDialog//CResizableDialog
{
	// friend classes ( part of the same dialog interface )
	friend class CLayersPropertyPage;
	friend class CDirectoriesPropertyPage;
	friend class CFileFiltersPropertyPage;
	friend class CDuplicatesPropertyPage;
	friend class CMarkersPropertyPage;
	friend class CProcessesPropertyPage;
	friend class CStatusLogPropertyPage;
	friend class COptionsPropertyPage;
 friend class CResizablePropertySheet;

public:
	
	CDuffDlg(CWnd* pParent = NULL);	// standard constructor

private:

	bool ClearResults();
	bool SaveLog();
	void Log(const CString);
	void Start();
	void Pause();
 int  Search();
	void Help();
	void SaveSettings();
	void LoadSettings();
	void StartPause();
	void Stop();
	bool Confirm();
	void Exit();
	int  LoadPlugins();

	static UINT myThread(LPVOID me); // *** static *** member function

private:

	CResizablePropertySheet  m_PropertySheet;
	CLayersPropertyPage      m_LayerPage;
	CFileFiltersPropertyPage m_FileFilterPage;
	CDirectoriesPropertyPage m_DirectoryPage;
	CDuplicatesPropertyPage  m_DuplicatePage;
	CProcessesPropertyPage   m_ProcessPage;
	CStatusLogPropertyPage   m_StatusLogPage;
	CMarkersPropertyPage     m_SelectionPage;
	COptionsPropertyPage     m_OptionsPage;
	CDuffPluginManager       m_PluginManager;

#ifdef _DEBUG
 CDebugPage               m_DebugPage;
#endif

	HACCEL      m_hAccel;
	bool        m_bAnimateControl;
	HICON       m_hIcon;
	CImageList  m_TabImageList;
 CWinThread *m_pWorkerThread;



// Dialog Data
	//{{AFX_DATA(CDuffDlg)
	enum { IDD = IDD_DUFF_DIALOG };
	CStatic	m_RangeEntire;
	CStatic	m_SubRange2;
	CStatic	m_SubRange1;
	CStatic	m_Status;
	CStatic	m_PropertySheetFrame;
	CProgressCtrl64	m_ProgressSub2;
	CProgressCtrl64	m_ProgressSub1;
	CButton	m_PauseCheckBox;
	CAnimateCtrl	m_AnimateControl;
	CButton	m_StopButton;
	CStatic	m_CurrentTaskInfoText;
	CProgressCtrl64	m_ProgressEntire;
	CStatic	m_CurrentTaskText;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDuffDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CDuffDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnHelpAbout();
	afx_msg void OnFileSave();
	afx_msg void OnFileLoad();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnFileExit();
	afx_msg void OnExit();
	afx_msg void OnStop();
	afx_msg void OnSearchPause();
	afx_msg void OnSearchStart();
	afx_msg void OnSearchStop();
	afx_msg void OnViewDiectories();
	afx_msg void OnViewDuplicates();
	afx_msg void OnViewLayers();
	afx_msg void OnViewLog();
	afx_msg void OnViewProcesses();
	afx_msg void OnViewSelections();
	afx_msg void OnFileSavelog();
	afx_msg void OnFileClearResults();
	afx_msg void OnStart();
	afx_msg void OnPause();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnViewOptions();
	afx_msg void OnDestroy();
	afx_msg void OnViewFileFilters();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnHelpIndex();
	afx_msg void OnFileSaveGlobal();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnFileExportCsv();
	afx_msg void OnFileExportDuplic8();
	afx_msg void OnFileExportFnd();
	afx_msg void OnFileImportDuplic8();
	afx_msg void OnFileImportFnd();
	afx_msg void OnTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DUFFDLG_H__DD0D3E95_0F0A_473E_8CF5_EBC454DE9E75__INCLUDED_)
