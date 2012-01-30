// DuplicatesPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "PropertyPageDuplicates.h"
#include "duffdlg.h"
#include "TextClipboard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDuplicatesPropertyPage property page

IMPLEMENT_DYNCREATE(CDuplicatesPropertyPage, CResizablePage)

CDuplicatesPropertyPage::CDuplicatesPropertyPage() : CResizablePage(CDuplicatesPropertyPage::IDD)
{
	//{{AFX_DATA_INIT(CDuplicatesPropertyPage)
	//}}AFX_DATA_INIT
}

CDuplicatesPropertyPage::~CDuplicatesPropertyPage()
{
}

void CDuplicatesPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CResizablePage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDuplicatesPropertyPage)
	DDX_Control(pDX, IDC_DUPLICATE_LIST, m_DupeList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDuplicatesPropertyPage, CResizablePage)
	//{{AFX_MSG_MAP(CDuplicatesPropertyPage)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDuplicatesPropertyPage message handlers
BOOL CDuplicatesPropertyPage::OnInitDialog() 
{
	CResizablePage::OnInitDialog();

	// anchor dialog items 
 AddAnchor(IDC_DUPLICATE_LIST_FRAME,  TOP_LEFT,BOTTOM_RIGHT);	
 AddAnchor(IDC_DUPLICATE_LIST,  TOP_LEFT,BOTTOM_RIGHT);	
 AddAnchor(IDC_SELECTED_SIZE,  BOTTOM_LEFT);	
 AddAnchor(IDC_STATIC_SELECTED_SIZE,  BOTTOM_LEFT);	
 AddAnchor(IDC_TOTAL_CHECKED,  BOTTOM_LEFT);	
 AddAnchor(IDC_STATIC_CHECKED,  BOTTOM_LEFT);	
 AddAnchor(IDC_TOTAL_SIZE,  BOTTOM_LEFT);	
 AddAnchor(IDC_TOTAL_SELECTED,  BOTTOM_LEFT);	
 AddAnchor(IDC_TOTAL_COUNT,  BOTTOM_LEFT);	
 AddAnchor(IDC_STATIC_SELECTED,  BOTTOM_LEFT);	
 AddAnchor(IDC_STATIC_COUNT,  BOTTOM_LEFT);	
 AddAnchor(IDC_STATIC_SIZE,  BOTTOM_LEFT);	
 AddAnchor(IDC_STATIC_MARKED_SIZE,  BOTTOM_LEFT);	
 AddAnchor(IDC_MARKED_SIZE,  BOTTOM_LEFT);
 AddAnchor(IDC_TOTAL_DUPE_SIZE,  BOTTOM_LEFT);
 AddAnchor(IDC_STATIC_TOTAL_DUPE_SIZE,  BOTTOM_LEFT);
 AddAnchor(IDC_TOTAL_DUPLICATES,  BOTTOM_LEFT);
 AddAnchor(IDC_STATIC_DUPLICATES,  BOTTOM_LEFT);
 //

	// set up list info controls
	m_DupeList.SetTotalCheckedCtrl( (CEdit*)GetDlgItem(IDC_TOTAL_CHECKED) ); 
	m_DupeList.SetTotalCountCtrl( (CEdit*)GetDlgItem(IDC_TOTAL_COUNT) );
	m_DupeList.SetTotalBytesCtrl( (CEdit*)GetDlgItem(IDC_TOTAL_SIZE) );
	m_DupeList.SetNumSelectedCtrl( (CEdit*)GetDlgItem(IDC_TOTAL_SELECTED) ); 
	m_DupeList.SetSelectedBytesCtrl( (CEdit*)GetDlgItem(IDC_SELECTED_SIZE) );
	m_DupeList.SetMarkedBytesCtrl( (CEdit*)GetDlgItem(IDC_MARKED_SIZE) ); 

	m_DupeList.SetTotalDuplicateCtrl( (CEdit*)GetDlgItem(IDC_TOTAL_DUPLICATES) );
	m_DupeList.SetDuplicateBytesCtrl( (CEdit*)GetDlgItem(IDC_TOTAL_DUPE_SIZE) );
	

 //

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// let parent dialog know of keystrokes
BOOL CDuplicatesPropertyPage::PreTranslateMessage(MSG* pMsg) 
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

void CDuplicatesPropertyPage::LoadSettings()
{
//	MessageBox("loading settings");
}

void CDuplicatesPropertyPage::SaveSettings()
{
// MessageBox("save settings");
}

void CDuplicatesPropertyPage::AddItem(CFileInfo *pFileInfo)
{
 m_DupeList.AddItem(pFileInfo);
}

ULONGLONG CDuplicatesPropertyPage::GetNumFiles()
{
 return m_DupeList.GetTotalFilesCounter();
}

void CDuplicatesPropertyPage::UpdateListMarks()
{
 m_DupeList.UpdateListMarks();
}
