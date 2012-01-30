// OptionsGeneralForm.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "OptionsGeneralForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "DuplicateListCtrl.h"

extern CDuffApp theApp;

//CArray <CDuplicateListColumn *, CDuplicateListColumn* > CDuplicateListCtrl::m_Columns;

/////////////////////////////////////////////////////////////////////////////
// COptionsGeneralForm dialog


COptionsGeneralForm::COptionsGeneralForm(CWnd* pParent /*=NULL*/) 
: CDialog(COptionsGeneralForm::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionsGeneralForm)
	//}}AFX_DATA_INIT

	m_Name = StringFromResource(IDS_OPTIONS_GENERAL);
}


void COptionsGeneralForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsGeneralForm)
	DDX_Control(pDX, IDC_THREAD_PRIORITY, m_ThreadPriority);
	DDX_Control(pDX, IDC_PROGRESS_UPDATE_INTERVAL, m_UpdateInterval);
	DDX_Control(pDX, IDC_NO_ACCESS_RETRY, m_NoAccessRetry);
	DDX_Control(pDX, IDC_AUTOSCROLL_DUPE_LIST, m_AutoScrollDupeList);
	DDX_Control(pDX, IDC_TOOLTIP_TEXTS, m_ToolTipTexts);
	DDX_Control(pDX, IDC_TOOLTIP_FORMAT, m_ToolTipFormat);
	DDX_Control(pDX, IDC_SHOW_TOOLTIPS, m_ShowToolTips);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsGeneralForm, CDialog)
	//{{AFX_MSG_MAP(COptionsGeneralForm)
	ON_BN_CLICKED(IDC_SHOW_TOOLTIPS, OnShowTooltips)
	ON_LBN_DBLCLK(IDC_TOOLTIP_TEXTS, OnDblclkTooltipTexts)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsGeneralForm message handlers

void COptionsGeneralForm::OnOK() 
{
}

void COptionsGeneralForm::OnCancel() 
{
}

void COptionsGeneralForm::OnShowTooltips() 
{
	bool show = m_ShowToolTips.GetCheck() == BST_CHECKED;
	m_ToolTipFormat.EnableWindow(show);
	m_ToolTipTexts.EnableWindow(show);
	GetDlgItem(IDC_STATIC_TOOLTIP_FORMAT)->EnableWindow(show);
	GetDlgItem(IDC_STATIC_TOOLTIP_TEXTS)->EnableWindow(show);

}

BOOL COptionsGeneralForm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

 CString sTemp;
	for ( int i = 0; i < CDuplicateListCtrl::m_Columns.GetSize(); i++ )
	{
		sTemp.Format( _T("%%%c\t%s") , _T('a') + i, CDuplicateListCtrl::m_Columns.ElementAt(i)->GetName() );
  m_ToolTipTexts.AddString(sTemp);
	}


	LoadOptions();
 OnShowTooltips();	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void COptionsGeneralForm::OnDblclkTooltipTexts() 
{
 CString sTemp;
	sTemp.Format( _T("%%%c") , _T('a') + m_ToolTipTexts.GetCurSel() );
 m_ToolTipFormat.ReplaceSel(sTemp,TRUE);
}

bool COptionsGeneralForm::SaveOptions()
{
	CString sTemp;
 int iTemp;

	// 'autoscroll duplicate list' ( checkbox )
	m_pDuffOptions->General.AutoScrollDupeList = m_AutoScrollDupeList.GetCheck() == BST_CHECKED;
	//

	// 'no access retry' ( checkbox )
 m_pDuffOptions->General.NoAccessRetry = m_NoAccessRetry.GetCheck() == BST_CHECKED;
	//

	// 'update progress every XXX milliseconds ( numedit )
	m_UpdateInterval.GetWindowText(sTemp);
 iTemp = _ttoi(sTemp);
	m_pDuffOptions->General.UpdateInterval = iTemp;
	//

	// 'thread priority' ( combo box )
	m_pDuffOptions->General.ThreadPriority = m_ThreadPriority.GetCurSel();
 //

	// 'tool tip format' ( edit )
 m_ToolTipFormat.GetWindowText( sTemp );
	_tcscpy(m_pDuffOptions->General.ToolTipText, sTemp);
	//

	// 'show tool tips' ( checkbox )
	m_pDuffOptions->General.UseToolTip = m_ShowToolTips.GetCheck() == BST_CHECKED;
	//

 return true;
}

bool COptionsGeneralForm::LoadOptions()
{
 CString sTemp;

	// 'autoscroll duplicate list' ( checkbox )
	m_AutoScrollDupeList.SetCheck( m_pDuffOptions->General.AutoScrollDupeList ? BST_CHECKED : BST_UNCHECKED );
 //
	
	// 'no access retry' ( checkbox )
 m_NoAccessRetry.SetCheck( m_pDuffOptions->General.NoAccessRetry ? BST_CHECKED : BST_UNCHECKED );
 //
	
	// 'update progress every XXX milliseconds ( numedit )
 sTemp.Format( _T("%d") ,m_pDuffOptions->General.UpdateInterval);
	m_UpdateInterval.SetWindowText(sTemp);
 //

	// 'thread priority' ( combo box )
	m_ThreadPriority.SetCurSel(m_pDuffOptions->General.ThreadPriority);
 //

	// 'tool tip format' ( edit )
 m_ToolTipFormat.SetWindowText( m_pDuffOptions->General.ToolTipText );
	//

	// 'show tool tips' ( checkbox )
	m_ShowToolTips.SetCheck( m_pDuffOptions->General.UseToolTip ? BST_CHECKED : BST_UNCHECKED );
 OnShowTooltips();	
	//
	
	return true;
}

