// OptionsPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "PropertyPageOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CDuffApp theApp;

#include "OptionsSoundForm.h"

#include "DuffDlg.h"

/////////////////////////////////////////////////////////////////////////////
// COptionsPropertyPage property page

IMPLEMENT_DYNCREATE(COptionsPropertyPage, CResizablePage)

COptionsPropertyPage::COptionsPropertyPage() : CResizablePage(COptionsPropertyPage::IDD)
{
	//{{AFX_DATA_INIT(COptionsPropertyPage)
	//}}AFX_DATA_INIT
}

COptionsPropertyPage::~COptionsPropertyPage()
{
}

void COptionsPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CResizablePage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsPropertyPage)
	DDX_Control(pDX, IDC_OPTION_TITLE, m_OptionTitle);
	DDX_Control(pDX, IDC_OPTION_LIST, m_OptionList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsPropertyPage, CResizablePage)
	//{{AFX_MSG_MAP(COptionsPropertyPage)
	ON_LBN_SELCHANGE(IDC_OPTION_LIST, OnSelchangeOptionList)
	ON_BN_CLICKED(IDC_APPLY_CHANGES, OnApplyChanges)
	ON_BN_CLICKED(IDC_ABORT_CHANGES, OnAbortChanges)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsPropertyPage message handlers

BOOL COptionsPropertyPage::PreTranslateMessage(MSG* pMsg) 
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

BOOL COptionsPropertyPage::OnInitDialog() 
{
	CRect rcSheet;

	CResizablePage::OnInitDialog();

	// set up config form rect
	GetDlgItem( IDC_OPTION_FRAME )->GetWindowRect( &rcSheet );
	ScreenToClient( &rcSheet );
 //

	// setup individual config forms

 m_OptionList.AddString(m_OptionsGeneralForm.GetName());
	m_OptionList.SetItemData(0,(DWORD)&m_OptionsGeneralForm);
	m_OptionsGeneralForm.Create(IDD_OPTIONS_GENERAL, this);
	m_OptionsGeneralForm.SetWindowPos( NULL, rcSheet.left-7, rcSheet.top-7, 0, 0, 	SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE );
 
	m_OptionList.AddString(m_SoundOptionsDlg.GetName());
	m_OptionList.SetItemData(1,(DWORD)&m_SoundOptionsDlg);
 m_SoundOptionsDlg.Create(IDD_OPTIONS_SOUNDS_FORM, this);
	m_SoundOptionsDlg.SetWindowPos( NULL, rcSheet.left-7, rcSheet.top-7, 0, 0, 	SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE );
	
	m_OptionList.AddString(m_MarkerOptionsForm.GetName());
	m_OptionList.SetItemData(2,(DWORD)&m_MarkerOptionsForm);
	m_MarkerOptionsForm.Create(IDD_MARKER_OPTIONS_FORM,this);
	m_MarkerOptionsForm.SetWindowPos( NULL, rcSheet.left-7, rcSheet.top-7, 0, 0, 	SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE );
	
	m_OptionList.AddString(m_ProcessOptionsForm.GetName());
	m_OptionList.SetItemData(3,(DWORD)&m_ProcessOptionsForm);
	m_ProcessOptionsForm.Create(IDD_OPTIONS_PROCESSES,this);
	m_ProcessOptionsForm.SetWindowPos( NULL, rcSheet.left-7, rcSheet.top-7, 0, 0, 	SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE );
 
 m_OptionList.SetCurSel(0);
 
	// load the initial options form
	UpdateForm();
	//
 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void COptionsPropertyPage::UpdateForm()
{
 int SelectedIndex;
 SelectedIndex = 	m_OptionList.GetCurSel(); 
	if ( SelectedIndex  != LB_ERR)
	{
		CDialog* pDlg;

		for (int Index = 0; Index < m_OptionList.GetCount(); Index++)
		{
			pDlg = (CDialog*)m_OptionList.GetItemData(Index);
	
			if ( pDlg )
			{
				pDlg->ShowWindow( Index == SelectedIndex ? SW_SHOW : SW_HIDE);
		 }
		}
	}	
}

void COptionsPropertyPage::OnSelchangeOptionList() 
{
 UpdateForm();
}


void COptionsPropertyPage::OnApplyChanges() 
{
	m_OptionsGeneralForm.SaveOptions();
 m_SoundOptionsDlg.SaveOptions();
 m_MarkerOptionsForm.SaveOptions();
 m_ProcessOptionsForm.SaveOptions();
}

void COptionsPropertyPage::OnAbortChanges() 
{
	m_OptionsGeneralForm.LoadOptions();
 m_SoundOptionsDlg.LoadOptions();
 m_MarkerOptionsForm.LoadOptions();
 m_ProcessOptionsForm.LoadOptions();
}

int COptionsPropertyPage::InitDupeFileFind(CDuplicateFileFind &)
{
	// save any settings that the m_ProcessOptionsForm object needs to know about
 CFileComparisonLayer::SetAccessRetry( !m_OptionsGeneralForm.m_NoAccessRetry );
	CFileMarker::SetMarkAtLeastOne( theApp.m_DuffOptions.Marker.MarkAtLeastOne );
	CFileMarker::SetMarkMode( theApp.m_DuffOptions.Marker.MarkMode );
 //

 return 0;
}
