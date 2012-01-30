// ProcessOptionsForm.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "OptionsProcessForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "util.h"

/////////////////////////////////////////////////////////////////////////////
// CProcessOptionsForm dialog


CProcessOptionsForm::CProcessOptionsForm(CWnd* pParent /*=NULL*/)
	: CDialog(CProcessOptionsForm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProcessOptionsForm)
	//}}AFX_DATA_INIT
	m_Name = StringFromResource(IDS_OPTIONS_PROCESSORS);
}


void CProcessOptionsForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProcessOptionsForm)
	DDX_Control(pDX, IDC_SET_PROCESS_WARNING, m_SetProcessWarning);
	DDX_Control(pDX, IDC_PROCESS_AUTO_PERFORM, m_AutoPerformProcesses);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProcessOptionsForm, CDialog)
	//{{AFX_MSG_MAP(CProcessOptionsForm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProcessOptionsForm message handlers

void CProcessOptionsForm::OnOK() 
{
}

void CProcessOptionsForm::OnCancel() 
{
}



bool CProcessOptionsForm::SaveOptions()
{

	m_pDuffOptions->Process.AutoPerformProcesses = m_AutoPerformProcesses.GetCheck() == BST_CHECKED;
 m_pDuffOptions->Process.DupeSetProcessWarning = m_SetProcessWarning.GetCheck() == BST_CHECKED; 


 return true;
}

bool CProcessOptionsForm::LoadOptions()
{

	m_AutoPerformProcesses.SetCheck(m_pDuffOptions->Process.AutoPerformProcesses ? BST_CHECKED : BST_UNCHECKED); 
	m_SetProcessWarning.SetCheck( m_pDuffOptions->Process.DupeSetProcessWarning ? BST_CHECKED : BST_UNCHECKED); 


	return true;
}


BOOL CProcessOptionsForm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
 LoadOptions();		

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
