// SelectionsPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "PropertyPageSelections.h"
#include "duffdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#include "DuplicateFileFind.h"

extern CDuplicateFileFind g_DupeFileFind;


/////////////////////////////////////////////////////////////////////////////
// CMarkersPropertyPage property page

IMPLEMENT_DYNCREATE(CMarkersPropertyPage, CResizablePage)

CMarkersPropertyPage::CMarkersPropertyPage() : CResizablePage(CMarkersPropertyPage::IDD)
{
	//{{AFX_DATA_INIT(CMarkersPropertyPage)
	//}}AFX_DATA_INIT
	m_pWorkerThread = NULL;
}

CMarkersPropertyPage::~CMarkersPropertyPage()
{
}

void CMarkersPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CResizablePage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMarkersPropertyPage)
	DDX_Control(pDX, IDC_NOCONFIG, m_NoConfigText);
	DDX_Control(pDX, IDC_SELECTION_DESCRIPTION, m_SelectionDescription);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMarkersPropertyPage, CResizablePage)
	//{{AFX_MSG_MAP(CMarkersPropertyPage)
	ON_BN_CLICKED(IDC_SELECTIONS_MAKE, OnSelectionsMake)
	ON_LBN_SELCHANGE(IDC_SELECTION_CHECKLIST, OnSelchangeSelectionChecklist)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMarkersPropertyPage message handlers

BOOL CMarkersPropertyPage::OnInitDialog() 
{
	CDialog     *pConfigDlg;
	CFileMarker *pMarker;
 int          Index;

	CResizablePage::OnInitDialog();
	
	// preset resize layout
	AddAnchor(IDC_SELECTION_CHECKLIST, TOP_LEFT,BOTTOM_LEFT);
	AddAnchor(IDC_SELECTION_FRAME,  TOP_LEFT,BOTTOM_LEFT);
	AddAnchor(IDC_SELECTION_INFO_FRAME,  TOP_LEFT,TOP_RIGHT);
	AddAnchor(IDC_SELECTION_DESCRIPTION,  TOP_LEFT,TOP_RIGHT);
	AddAnchor(IDC_SELECTION_CONFIG_FRAME, TOP_LEFT, BOTTOM_RIGHT);
	AddAnchor(IDC_PROPERTYSHEET,  TOP_LEFT, BOTTOM_RIGHT);
	AddAnchor(IDC_SELECTIONS_MAKE,  BOTTOM_LEFT);
 //

 // subclass checklistbox
 m_SelectionCheckList.SubclassDlgItem(IDC_SELECTION_CHECKLIST,this);
 //


	for (Index = 0; Index < g_DupeFileFind.GetFileSelectionArray()->GetSize(); Index++)
	{
		pMarker = g_DupeFileFind.GetFileSelectionArray()->GetAt(Index);
		pConfigDlg = pMarker->GetForm();
				
	 if (pConfigDlg)
		{
 		CRect rcSheet;
			pConfigDlg->Create(pMarker->GetFormID(), this);
			GetDlgItem( IDC_PROPERTYSHEET )->GetWindowRect( &rcSheet );
			ScreenToClient( &rcSheet );
			pConfigDlg->SetWindowPos( NULL, rcSheet.left-7, rcSheet.top-7, 0, 0, 	SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE );
			pConfigDlg->UpdateData();
 	}
	 m_SelectionCheckList.AddString ( pMarker->GetName() );
  m_SelectionCheckList.SetItemData ( Index, (DWORD)pMarker );
	}

	if ( m_SelectionCheckList.GetCount() != 0 )
	{
		m_SelectionCheckList.SetCurSel(0);
  UpdateForm();	
	}


// CANNOT LOG HERE

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}




void CMarkersPropertyPage::UpdateForm()
{
	CDialog     *pConfigDlg;
 CFileMarker *pSelectedMarker;
 CFileMarker *pCurrentMarker;
 int Index;

	if (m_SelectionCheckList.GetCurSel() != LB_ERR  )
	{
	 pSelectedMarker = (CFileMarker *)m_SelectionCheckList.GetItemData(	m_SelectionCheckList.GetCurSel() );
		
		m_SelectionDescription.SetWindowText( pSelectedMarker->GetDescription() );

		for (Index = 0; Index < g_DupeFileFind.GetFileSelectionArray()->GetSize(); Index++)
		{
			pCurrentMarker = g_DupeFileFind.GetFileSelectionArray()->GetAt(Index);
			pConfigDlg = pCurrentMarker->GetForm();
	
			if (pConfigDlg)
			{
				pConfigDlg->ShowWindow( pCurrentMarker == pSelectedMarker ? SW_SHOW : SW_HIDE);
		 }
		}

		pConfigDlg = pSelectedMarker->GetForm();
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



// m_pWorkerThread = AfxBeginThread(myThread, this,Priority);	

// UINT CDuffDlg::myThread(LPVOID me) 


UINT CMarkersPropertyPage::PerformSelections()
{
	UINT Ret;
	Ret = g_DupeFileFind.ExecuteMarkers();					

	return Ret;
}

UINT CMarkersPropertyPage::PerformSelectionsThread(LPVOID pMe)
{

 UINT Ret;

 CMarkersPropertyPage * self = (CMarkersPropertyPage *)pMe;
 Ret = self->PerformSelections();

	// tell the duplicate list box to update itself
//	((CDuffDlg*)pDlg->GetParent()->GetParent())->m_DuplicatePage.UpdateListMarks();
 //
 
	return Ret;
}

void CMarkersPropertyPage::OnSelectionsMake() 
{
	CString Temp, Msg;
 int iIndex;
	
	// select the checked markers
	for (iIndex = 0; iIndex < m_SelectionCheckList.GetCount(); iIndex++)
	{
		if ( m_SelectionCheckList.GetCheck(iIndex) == BST_CHECKED )
		{
   ((CFileMarker*)m_SelectionCheckList.GetItemData(iIndex))->SetSelected(true);
		}
	}
	//

	if ( g_DupeFileFind.m_DuffStatus.Status == DUFFSTATUS_STOPPED )
	{
	

//		Msg = "Are you sure you want to peform the checked selections?"; //.Format("Are you sure you want to all the selected files ?",buffer);
	///	if ( MessageBox(Msg, "Confirm", MB_YESNO) == IDYES )
	//	{
			g_DupeFileFind.m_DuffStatus.Status = DUFFSTATUS_RUNNING;
			m_pWorkerThread = AfxBeginThread(PerformSelectionsThread, this,THREAD_PRIORITY_NORMAL);
 SetTimer(PROGRESS_TIMER, 100, NULL);
	//	}
	}
 else
	{
		MessageBox( _T("Can't run while searching for duplicates") );
	}

}



BOOL CMarkersPropertyPage::PreTranslateMessage(MSG* pMsg) 
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


void CMarkersPropertyPage::OnSelchangeSelectionChecklist() 
{
 UpdateForm();	
}

int CMarkersPropertyPage::InitDupeFileFind(CDuplicateFileFind & )
{
	// save marker settings to DupeFileFind
	//

 return -1;
}

void CMarkersPropertyPage::OnTimer(UINT nIDEvent) 
{

 if ( nIDEvent == PROGRESS_TIMER )
	{

		
		
		
		
		

		

int i;
	CString Temp;
 CFileInfo * pFileInfo;
 int PercentDone;
 CDuffDlg *pDuffDlg = (CDuffDlg*)GetParent()->GetParent();

	if ( g_DupeFileFind.m_DuffStatus.LockIfUnlocked() )
	{

 pDuffDlg->m_CurrentTaskText.SetWindowText(g_DupeFileFind.m_DuffStatus.CurrentTaskStr );
	pDuffDlg->m_CurrentTaskInfoText.SetWindowText(g_DupeFileFind.m_DuffStatus.CurrentTaskInfo );
 pDuffDlg->m_ProgressEntire.SetRange64( g_DupeFileFind.m_DuffStatus.MainProgress.Min, g_DupeFileFind.m_DuffStatus.MainProgress.Max );
 pDuffDlg->m_ProgressEntire.SetPos64( g_DupeFileFind.m_DuffStatus.MainProgress.Pos );
 PercentDone = 0;
	if ( g_DupeFileFind.m_DuffStatus.MainProgress.Max )
 	PercentDone = (int) ( 100 * (double)g_DupeFileFind.m_DuffStatus.MainProgress.Pos/ (double)g_DupeFileFind.m_DuffStatus.MainProgress.Max);
	Temp.Format( _T("%03d %%") ,PercentDone);
	pDuffDlg->m_RangeEntire.SetWindowText(Temp);

 pDuffDlg->m_ProgressSub1.SetRange64( g_DupeFileFind.m_DuffStatus.SubProgress1.Min, g_DupeFileFind.m_DuffStatus.SubProgress1.Max );
 pDuffDlg->m_ProgressSub1.SetPos64( g_DupeFileFind.m_DuffStatus.SubProgress1.Pos );
 
	PercentDone = 0;
	if ( g_DupeFileFind.m_DuffStatus.SubProgress1.Max )
	 PercentDone = (int)(100 * (double)g_DupeFileFind.m_DuffStatus.SubProgress1.Pos / (double)g_DupeFileFind.m_DuffStatus.SubProgress1.Max);
	
	Temp.Format( _T("%03d %%") ,PercentDone);
	pDuffDlg->m_SubRange1.SetWindowText(Temp);

 pDuffDlg->m_ProgressSub2.SetRange64( g_DupeFileFind.m_DuffStatus.SubProgress2.Min, g_DupeFileFind.m_DuffStatus.SubProgress2.Max );
 pDuffDlg->m_ProgressSub2.SetPos64( g_DupeFileFind.m_DuffStatus.SubProgress2.Pos );
 PercentDone = 0;
	if ( g_DupeFileFind.m_DuffStatus.SubProgress2.Max )
		PercentDone = (int)(100 * (double)g_DupeFileFind.m_DuffStatus.SubProgress2.Pos / (double)g_DupeFileFind.m_DuffStatus.SubProgress2.Max);
	Temp.Format( _T("%03d %%") ,PercentDone);
	pDuffDlg->m_SubRange2.SetWindowText(Temp);

	for ( i = 0; i < g_DupeFileFind.m_DuffStatus.LogQueue.GetSize(); i++ )
	{
  pDuffDlg->Log( g_DupeFileFind.m_DuffStatus.LogQueue.ElementAt(i) );
	}
	g_DupeFileFind.m_DuffStatus.LogQueue.RemoveAll();
 
	//if ( g_DupeFileFind.m_DuffStatus.DupeQueue.GetSize() && m_OptionsPage.m_DuffOptions.Sound.Enabled )
	//{
	//	PlaySoundFile( m_OptionsPage.m_DuffOptions.Sound.FoundDuplicate);
	//}

 for ( i = 0; i < g_DupeFileFind.m_DuffStatus.DupeQueue.GetSize(); i++ )
	{
		pFileInfo = g_DupeFileFind.m_DuffStatus.DupeQueue.ElementAt(i);

		pDuffDlg->m_DuplicatePage.AddItem(pFileInfo);
		/*

	 if ( pFileInfo->FirstFile )
		{
			m_DuplicatePage.m_DuplicateSetCounter ++;
		}

		// add duplicates to list view
  Temp.Format("%d", m_DuplicatePage.m_DuplicateSetCounter);
		m_DuplicatePage.m_DupeList.InsertItem(LVIF_PARAM | LVIF_TEXT, m_DuplicatePage.m_TotalFilesCounter, Temp,NULL,NULL,NULL,(DWORD) pFileInfo );
		m_DuplicatePage.m_DupeList.SetItemText( m_DuplicatePage.m_TotalFilesCounter-1,1, pFileInfo ->FullName    );
		buffer[0] = 0;
		ulonglong2str(buffer,pFileInfo->Size);
		m_DuplicatePage.m_DupeList.SetItemText( m_DuplicatePage.m_TotalFilesCounter-1,2,buffer);
		pFileInfo->InitVersion();
		m_DuplicatePage.m_DupeList.SetItemText( m_DuplicatePage.m_TotalFilesCounter-1,3, pFileInfo->GetFileVersionStr());
  //  
  
		*/

	}
	g_DupeFileFind.m_DuffStatus.DupeQueue.RemoveAll();
 
 //if ( m_OptionsPage.m_DuffOptions.General.AutoScrollDupeList  ) 
	//{
		//if ( (unsigned long)(m_DuplicatePage.m_DupeList.GetTopIndex() + m_DuplicatePage.m_DupeList.GetCountPerPage()) == m_DuplicatePage.m_TotalFilesCounter -1 ||
		//	(unsigned long)(m_DuplicatePage.m_DupeList.GetCountPerPage()) >   m_DuplicatePage.m_TotalFilesCounter -1
		//	)
 	// m_DuplicatePage.m_DupeList.EnsureVisible(m_DuplicatePage.GetNumFiles()-1, FALSE);
	//}

	 g_DupeFileFind.m_DuffStatus.Unlock();

	}





		
		
		
		
		if ( g_DupeFileFind.m_DuffStatus.Status == DUFFSTATUS_STOPPED )
		{
			KillTimer(nIDEvent);
			((CDuffDlg*)GetParent()->GetParent())->m_DuplicatePage.UpdateListMarks();
		}
	}

	CResizablePage::OnTimer(nIDEvent);
}
