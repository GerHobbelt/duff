// ProcessesPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "PropertyPageProcesses.h"
#include"duffdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "DuplicateFileFind.h"

extern CDuplicateFileFind g_DupeFileFind;
extern CDuffApp theApp;

#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CProcessesPropertyPage property page

IMPLEMENT_DYNCREATE(CProcessesPropertyPage, CResizablePage)

CProcessesPropertyPage::CProcessesPropertyPage() : CResizablePage(CProcessesPropertyPage::IDD)
{
	//{{AFX_DATA_INIT(CProcessesPropertyPage)
	//}}AFX_DATA_INIT
}

CProcessesPropertyPage::~CProcessesPropertyPage()
{
}

void CProcessesPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CResizablePage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProcessesPropertyPage)
	DDX_Control(pDX, IDC_NOCONFIG, m_NoConfigText);
	DDX_Control(pDX, IDC_PROCESS_DESCRIPTION, m_ProcessDescription);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProcessesPropertyPage, CResizablePage)
	//{{AFX_MSG_MAP(CProcessesPropertyPage)
	ON_BN_CLICKED(IDC_PERFORM, OnPerform)
	ON_LBN_SELCHANGE(IDC_PROCESS_CHECKLIST, OnSelchangeProcessChecklist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProcessesPropertyPage message handlers

BOOL CProcessesPropertyPage::OnInitDialog()
{
	CDialog* pConfigDlg;
 int Index;
	CFileProcessor *pFileProcessor;

	CResizablePage::OnInitDialog();

	// subclass checklistbox
	m_ProcessCheckList.SubclassDlgItem(IDC_PROCESS_CHECKLIST,this);
 //

	// preset resize layout
	AddAnchor(IDC_PROCESS_CHECKLIST, TOP_LEFT,BOTTOM_LEFT);
	AddAnchor(IDC_PROCESS_FRAME,  TOP_LEFT,BOTTOM_LEFT);
	AddAnchor(IDC_PROCESS_INFO_FRAME,  TOP_LEFT,TOP_RIGHT);
	AddAnchor(IDC_PROCESS_DESCRIPTION,  TOP_LEFT,TOP_RIGHT);
	AddAnchor(IDC_PROCESS_CONFIG_FRAME, TOP_LEFT, BOTTOM_RIGHT);
	AddAnchor(IDC_PROPERTYSHEET,  TOP_LEFT, BOTTOM_RIGHT);
	AddAnchor(IDC_PERFORM,  BOTTOM_LEFT);
 //

	// load file processors checklistbox
	for (Index = 0; Index < g_DupeFileFind.GetFileProcessArray()->GetSize(); Index++)
	{
		pFileProcessor = g_DupeFileFind.GetFileProcessArray()->GetAt(Index);
		pConfigDlg = pFileProcessor->GetForm();

	 if (pConfigDlg)
		{
 		CRect rcSheet;
			pConfigDlg->Create ( pFileProcessor->GetFormID(), this );
			GetDlgItem( IDC_PROPERTYSHEET )->GetWindowRect( &rcSheet );
			ScreenToClient( &rcSheet );
			pConfigDlg->SetWindowPos( NULL, rcSheet.left-7, rcSheet.top-7, 0, 0, 	SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE );
			pConfigDlg->UpdateData();
 	}

	 m_ProcessCheckList.AddString ( pFileProcessor->GetName() );
  m_ProcessCheckList.SetItemData ( Index,(DWORD)pFileProcessor );
	}

 // show initial config dialog
	if ( m_ProcessCheckList.GetCount() != 0 )
	{
		m_ProcessCheckList.SetCurSel(0);
  UpdateForm();
	}
	//

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


 UINT CProcessesPropertyPage::PerformProcessesThread(LPVOID pMe)
{

 UINT Ret;

 CProcessesPropertyPage * self = (CProcessesPropertyPage *)pMe;
 Ret = self->PerformProcesses();

	// tell the duplicate list box to update itself
//	((CDuffDlg*)pDlg->GetParent()->GetParent())->m_DuplicatePage.UpdateListMarks();
 //

	return Ret;

}

UINT CProcessesPropertyPage::PerformProcesses()
{
	UINT Ret;
	Ret = g_DupeFileFind.ExecuteProcesses();

	return Ret;

}


void CProcessesPropertyPage::OnPerform()
{
	CString Temp, Msg;
//	CArray<CFileInfo *, CFileInfo *> FilesToProcess;
 CFileProcessor *pProcessor;

//	((CDuffDlg*)GetParent()->GetParent())->SetTimer(0,100,NULL);

		// build file list

	  // warn if trying to process all files in any duplicate set
		bool DoIt = true;
		if ( theApp.m_DuffOptions.Process.DupeSetProcessWarning && g_DupeFileFind.CheckForFullSetMarks() )
		{
		 DoIt =	MessageBox( StringFromResource(IDS_CONFIRM_PROCESS_FULL_SET) ,StringFromResource(IDS_CONFIRMATION) ,MB_YESNO | MB_ICONQUESTION) == IDYES;
		}

if (!DoIt)
 return;

		// select the checked processors
	int		Index;

  g_DupeFileFind.RemoveAllFileProcessors();

		for ( Index = 0; Index < m_ProcessCheckList.GetCount(); Index++)
		{
			pProcessor = (CFileProcessor*)m_ProcessCheckList.GetItemData(Index);
		 pProcessor->SetSelected( m_ProcessCheckList.GetCheck(Index) == BST_CHECKED );
			pProcessor->UpdateData(true);
   g_DupeFileFind.AddFileProcessor(pProcessor);
		}

	/*
		for ( Index = 0; Index < ((CDuffDlg*)GetParent()->GetParent())->m_DuplicatePage.m_DupeList.GetItemCount(); Index++)
		{
			if ( ((CDuffDlg*)GetParent()->GetParent())->m_DuplicatePage.m_DupeList.GetCheck(Index) )
			{
				FilesToProcess.Add( (CFileInfo *)((CDuffDlg*)GetParent()->GetParent())->m_DuplicatePage.m_DupeList.GetItemData( Index ) );
   }
		}
*/
//



	if ( g_DupeFileFind.m_DuffStatus.Status == DUFFSTATUS_STOPPED )
	{
		g_DupeFileFind.m_DuffStatus.Status = DUFFSTATUS_RUNNING;
		m_pWorkerThread = AfxBeginThread(PerformProcessesThread, this,THREAD_PRIORITY_NORMAL);
  ((CDuffDlg*)GetParent()->GetParent())->SetTimer(PROGRESS_TIMER, 100, NULL);
	}
 else
	{
		MessageBox( _T("Can't run while busy") );
	}

/*

	if ( g_DupeFileFind.m_DuffStatus.Status == DUFFSTATUS_STOPPED )
	{

		for ( Index = 0; Index < m_ProcessCheckList.GetCount(); Index++)
		{

			if ( m_ProcessCheckList.GetCheck(Index) )
			{
				pProcessor = (CFileProcessor*)m_ProcessCheckList.GetItemData(Index);
					pProcessor->UpdateData(true);

				pProcessor->ProcessFiles( FilesToProcess );
			}

		}


((CDuffDlg*)GetParent()->GetParent())->KillTimer(0);

			((CDuffDlg*)GetParent()->GetParent())->m_ProgressEntire.SetPos(0);

((CDuffDlg*)GetParent()->GetParent())->m_CurrentTaskText.SetWindowText( StringFromResource(IDS_STATUS_IDLE) );

((CDuffDlg*)GetParent()->GetParent())->m_CurrentTaskInfoText.SetWindowText( NULL_STR );

		*/

 // update progress information
	g_DupeFileFind.m_DuffStatus.Lock();
	g_DupeFileFind.m_DuffStatus.CurrentTaskStr = "";
	g_DupeFileFind.m_DuffStatus.CurrentTaskInfo = "";
	g_DupeFileFind.m_DuffStatus.SubProgress1.Min = 0;
	g_DupeFileFind.m_DuffStatus.SubProgress1.Pos = 0;
	g_DupeFileFind.m_DuffStatus.SubProgress1.Max = 0;
	g_DupeFileFind.m_DuffStatus.Unlock();
	//

}

BOOL CProcessesPropertyPage::PreTranslateMessage(MSG* pMsg)
{
	bool ret;
	if ( IsDialogMessage( pMsg ) )
	{
		if ( TranslateAccelerator ( GetSafeHwnd(),((CDuffDlg*)GetParent()->GetParent())->m_hAccel,pMsg) )
  {
   TranslateMessage(pMsg);
   DispatchMessage(pMsg);
   ret = false;
		}
		ret = true;
	}
	else
	{
		ret = ( CWnd::PreTranslateMessage( pMsg ) != 0);
	}
	return ret;
}



void CProcessesPropertyPage::UpdateForm()
{
 CDialog        *pConfigDlg;
 CFileProcessor *pProcessor;
	CFileProcessor *pSelectedProcessor;
 int Index;

	if (m_ProcessCheckList.GetCurSel() != LB_ERR)
	{
		pSelectedProcessor = (CFileProcessor *)m_ProcessCheckList.GetItemData(	m_ProcessCheckList.GetCurSel() );
		m_ProcessDescription.SetWindowText( pSelectedProcessor->GetDescription()  );

		for (Index = 0; Index < m_ProcessCheckList.GetCount(); Index++)
		{
			pProcessor = ( CFileProcessor *)	m_ProcessCheckList.GetItemData(Index);
			pConfigDlg = pProcessor->GetForm();
			if ( pConfigDlg )
			{
				pConfigDlg->ShowWindow( ( pSelectedProcessor == pProcessor ) ? SW_SHOW : SW_HIDE);
		 }
		}

		pConfigDlg = pSelectedProcessor->GetForm();
		if (pConfigDlg)
		{
			m_NoConfigText.ModifyStyle(WS_VISIBLE,NULL);
		}
		else
		{
			m_NoConfigText.ModifyStyle(NULL,WS_VISIBLE);
		}
	}


}


void CProcessesPropertyPage::OnSelchangeProcessChecklist()
{
	UpdateForm();
}

void CProcessesPropertyPage::AddPlugin(CDuffPlugin * pPlugin)
{
 AddProcessor( pPlugin->GetInstance(), (CFileProcessor*) pPlugin->GetPrimaryModule() );
}

void CProcessesPropertyPage::AddProcessor(HINSTANCE hInstance, CFileProcessor * pProcessor)
{
 CDialog *pDlg;
 HRSRC resrc = NULL;

	pDlg = pProcessor->GetForm();
	if (pDlg)
	{
  resrc = FindResource(hInstance,(LPCTSTR)pProcessor->GetFormID(),RT_DIALOG);
  if (resrc)
		{
			HGLOBAL  hGlobal = LoadResource(hInstance,resrc);
			if (hGlobal)
			{
				hGlobal = LockResource(hGlobal);
				if ( hGlobal)
				if ( pDlg->CreateIndirect(hGlobal,this) )
				{
 			CRect rcSheet;
			//	pDlg->Create(g_DupeFileFind.GetFileProcessArray()->GetAt(Index)->GetFormID(), this);
				GetDlgItem( IDC_PROPERTYSHEET )->GetWindowRect( &rcSheet );
				ScreenToClient( &rcSheet );
				pDlg->SetWindowPos( NULL, rcSheet.left-7, rcSheet.top-7, 0, 0, 	SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE );
//							pDlg->UpdateData();
			//	CString Msg;
			//	Msg.Format("Loaded '%s' %s plugin (%s)",pProcessor->GetName(), "processor","sendto.dll");
//							((CDuffDlg*)GetParent()->GetParent())->Log(Msg);
				}

			}
		}

	}

	ASSERT( !pDlg || resrc );

	m_ProcessCheckList.AddString(pProcessor->GetName());
	m_ProcessCheckList.SetItemData(m_ProcessCheckList.GetCount()-1 ,(DWORD)pProcessor);

	if ( m_ProcessCheckList.GetCount() == 1 )
	{
  m_ProcessCheckList.SetCurSel(0);
		UpdateForm();
	}
}

int CProcessesPropertyPage::InitDupeFileFind(CDuplicateFileFind & )
{
 // save file processor settings to DupeFileFind
	//

	return -1;
}

