// DebugPage.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "PropertyPageDebug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "DuplicateFileFind.h"
extern CDuplicateFileFind g_DupeFileFind;

/////////////////////////////////////////////////////////////////////////////
// CDebugPage property page

IMPLEMENT_DYNCREATE(CDebugPage, CPropertyPage)

CDebugPage::CDebugPage() : CPropertyPage(CDebugPage::IDD)
{
	//{{AFX_DATA_INIT(CDebugPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDebugPage::~CDebugPage()
{
}

void CDebugPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDebugPage)
	DDX_Control(pDX, IDC_FILEINFO_COUNT, m_FileInfoCount);
	DDX_Control(pDX, IDC_FILES, m_Files);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDebugPage, CPropertyPage)
	//{{AFX_MSG_MAP(CDebugPage)
	ON_BN_CLICKED(IDC_READ_FILES, OnReadFiles)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDebugPage message handlers

void CDebugPage::OnReadFiles() 
{
 	
}

void CDebugPage::OnTimer(UINT nIDEvent) 
{
	#ifdef _DEBUG


	CString Temp;
	Temp.Format( _T("Number of CFileInfos currently allocated: %d"), CFileInfo::GetCount() );
	m_FileInfoCount.SetWindowText(Temp);
	#endif

	CPropertyPage::OnTimer(nIDEvent);
}

BOOL CDebugPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	
	#ifdef _DEBUG
 SetTimer(1,1000,NULL);	
	#endif
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

