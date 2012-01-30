// FileFiltersPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "PropertyPageFilters.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "DuffDlg.h"

#include "DuplicateFileFind.h"
extern CDuplicateFileFind g_DupeFileFind;

/////////////////////////////////////////////////////////////////////////////
// CFileFiltersPropertyPage property page

IMPLEMENT_DYNCREATE(CFileFiltersPropertyPage, CResizablePage)

CFileFiltersPropertyPage::CFileFiltersPropertyPage() : CResizablePage(CFileFiltersPropertyPage::IDD)
{
	//{{AFX_DATA_INIT(CFileFiltersPropertyPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CFileFiltersPropertyPage::~CFileFiltersPropertyPage()
{
}

void CFileFiltersPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CResizablePage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileFiltersPropertyPage)
	DDX_Control(pDX, IDC_NOCONFIG, m_NoConfigText);
	DDX_Control(pDX, IDC_FILTER_DESCRIPTION, m_FilterDescription);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileFiltersPropertyPage, CResizablePage)
	//{{AFX_MSG_MAP(CFileFiltersPropertyPage)
	ON_LBN_SELCHANGE(IDC_FILTER_CHECKLIST, OnSelchangeFilterChecklist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileFiltersPropertyPage message handlers

BOOL CFileFiltersPropertyPage::OnInitDialog() 
{
	CDialog* pConfigDlg;
	CFileFilter *pFileFilter;
 CRect rcSheet;	
 int Index;

	CResizablePage::OnInitDialog();

	// subclass checklistbox
 m_FilterCheckList.SubclassDlgItem(IDC_FILTER_CHECKLIST,this);
	//

	// preset resize layout
	AddAnchor(IDC_FILTER_CHECKLIST, TOP_LEFT,BOTTOM_LEFT);
	AddAnchor(IDC_FILE_FILTERS_FRAME,  TOP_LEFT,BOTTOM_LEFT);
	AddAnchor(IDC_FILTER_INFO_FRAME,  TOP_LEFT,TOP_RIGHT);
	AddAnchor(IDC_FILTER_DESCRIPTION,  TOP_LEFT,TOP_RIGHT);
	AddAnchor(IDC_FILTER_CONFIG_FRAME, TOP_LEFT, BOTTOM_RIGHT);
	AddAnchor(IDC_PROPERTYSHEET,  TOP_LEFT, BOTTOM_RIGHT);
 //

 // load file filter checklistbox		
	for (Index = 0; Index < g_DupeFileFind.GetFileFilterArray()->GetSize(); Index++)
	{
		pFileFilter = g_DupeFileFind.GetFileFilterArray()->GetAt(Index);
		pConfigDlg = pFileFilter->GetForm();		
	 if (pConfigDlg)
		{
			pConfigDlg->Create ( pFileFilter->GetFormID(), this );
			GetDlgItem( IDC_PROPERTYSHEET )->GetWindowRect( &rcSheet );
			ScreenToClient( &rcSheet );
			pConfigDlg->SetWindowPos( NULL, rcSheet.left-7, rcSheet.top-7, 0, 0, 	SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE );
	//?		pConfigDlg->UpdateData();
		}
  m_FilterCheckList.AddString ( pFileFilter->GetName() );
		m_FilterCheckList.SetItemData ( Index,(DWORD)pFileFilter );
	}
 //

	// show the initial config dialog
	if ( m_FilterCheckList.GetCount() != 0 )
	{
		m_FilterCheckList.SetCurSel(0);
  UpdateForm();	
	}
	//

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CFileFiltersPropertyPage::OnSelchangeFilterChecklist() 
{
 UpdateForm();	
}

void CFileFiltersPropertyPage::UpdateForm()
{
	CDialog* pDlg;
	CFileFilter * pSelectedFilter;
	CFileFilter * pCurrentFilter;

	if ( m_FilterCheckList.GetCurSel()  != LB_ERR)
	{
		pSelectedFilter = 	(CFileFilter *)m_FilterCheckList.GetItemData( m_FilterCheckList.GetCurSel());
		m_FilterDescription.SetWindowText( pSelectedFilter->GetDescription()  );

		for (int Index = 0; Index < g_DupeFileFind.GetFileFilterArray()->GetSize(); Index++)
		{
			pCurrentFilter = g_DupeFileFind.GetFileFilterArray()->GetAt(Index);
			pDlg = pCurrentFilter->GetForm();
		
			if (pDlg )
			{
				pDlg->ShowWindow( pSelectedFilter == pCurrentFilter ? SW_SHOW : SW_HIDE);
		 }
		}

		pDlg = pSelectedFilter->GetForm();
		if (pDlg)
		{
			m_NoConfigText.ShowWindow(SW_HIDE);
		}
		else
		{
			m_NoConfigText.ShowWindow(SW_SHOW);
		}
	}

}

BOOL CFileFiltersPropertyPage::PreTranslateMessage(MSG* pMsg) 
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

int CFileFiltersPropertyPage::InitDupeFileFind(CDuplicateFileFind & dff)
{
	int i;
 bool Cancel = false;

		// save all dialog data for file filters
	i = 0;

	//for ( i = 0; i < m_FilterCheckList.GetCount(); i ++)
	while ( !Cancel && i < m_FilterCheckList.GetCount() )
	{
		if ( ! dff.GetFileFilterArray()->GetAt(i)->UpdateData(true) )
		{
			((CResizablePropertySheet*)GetParent())->SetActivePage(this);
   m_FilterCheckList.SetCurSel(i);
			UpdateForm();	
			CDialog *pDlg = ((CFileFilter *)m_FilterCheckList.GetItemData(i))->GetForm();
			if (pDlg) pDlg->SetFocus();
			
			Cancel = true;
			break;
		}

		//m_FileFilters.ElementAt(i)->UpdateData(true);
		i++;
	}

	if ( Cancel )
		return i;

	for ( i = 0; i < m_FilterCheckList.GetCount(); i++ )
	{
		dff.SelectFilter(i, m_FilterCheckList.GetCheck(i) == BST_CHECKED);
	}

 return -1;
}
