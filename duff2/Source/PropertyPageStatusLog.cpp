// StatusLogPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "PropertyPageStatusLog.h"
#include "duffdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatusLogPropertyPage property page

IMPLEMENT_DYNCREATE(CStatusLogPropertyPage, CResizablePage)

CStatusLogPropertyPage::CStatusLogPropertyPage() : CResizablePage(CStatusLogPropertyPage::IDD)
{
	//{{AFX_DATA_INIT(CStatusLogPropertyPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CStatusLogPropertyPage::~CStatusLogPropertyPage()
{
}

void CStatusLogPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CResizablePage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatusLogPropertyPage)
	DDX_Control(pDX, IDC_STATUS_LOG, m_StatusLog);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStatusLogPropertyPage, CResizablePage)
	//{{AFX_MSG_MAP(CStatusLogPropertyPage)
	ON_BN_CLICKED(IDC_SAVE_LOG, OnSaveLog)
	ON_BN_CLICKED(IDC_CLEAR_LOG, OnClearLog)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatusLogPropertyPage message handlers

BOOL CStatusLogPropertyPage::OnInitDialog() 
{
	CResizablePage::OnInitDialog();
	

LOGFONT LogFont;
	long FontHeight = 12;
 
	if ( CWnd::GetFont()->GetLogFont(&LogFont) )
	{
		FontHeight = abs(LogFont.lfHeight);
	//	Msg.Format("Font Height: %d",FontHeight);
	}
	else
	{
//		Msg = "Unable to get font";
	}

 RECT rect;

	m_StatusLog.GetWindowRect(&rect);
 UINT StatusLogWidth = (rect.right - rect.left);

	m_StatusLog.SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP );
 m_StatusLog.InsertColumn(0, StringFromResource(IDS_LOGCOLUMN_DATETIME) ,  LVCFMT_LEFT,(int)(FontHeight * 9) );
	m_StatusLog.InsertColumn(1, StringFromResource(IDS_LOGCOLUMN_DESCRIPTION) ,LVCFMT_LEFT,(int)(StatusLogWidth * 0.80701754385964912280701754385965) );

	m_DescriptionColumn =   (rect.right - rect.left)-m_StatusLog.GetColumnWidth(1);


		// preset resize layout
	AddAnchor(IDC_STATUS_LOG_FRAME, TOP_LEFT,BOTTOM_RIGHT);
	AddAnchor(IDC_STATUS_LOG, TOP_LEFT,BOTTOM_RIGHT);
	AddAnchor(IDC_SAVE_LOG, BOTTOM_LEFT);
	AddAnchor(IDC_CLEAR_LOG, BOTTOM_LEFT);
 //


	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStatusLogPropertyPage::OnSaveLog() 
{
	((CDuffDlg*)GetParent()->GetParent())->SaveLog();
}

void CStatusLogPropertyPage::OnClearLog() 
{
 m_StatusLog.DeleteAllItems();
	((CDuffDlg*)GetParent()->GetParent())->Log( StringFromResource(IDS_LOG_CLEARED) );
}

BOOL CStatusLogPropertyPage::PreTranslateMessage(MSG* pMsg) 
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



void CStatusLogPropertyPage::OnSize(UINT nType, int cx, int cy) 
{
	CResizablePage::OnSize(nType, cx, cy);
	
	if (m_StatusLog)
	{
  RECT rect;
	m_StatusLog.GetWindowRect(&rect);

	m_StatusLog.SetColumnWidth(1,(rect.right - rect.left) - int(m_DescriptionColumn) );


	}
	
}
