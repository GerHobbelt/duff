// FileDateFilterForm.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "FilterFileDateForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileDateFilterForm dialog


CFileDateFilterForm::CFileDateFilterForm(CWnd* pParent /*=NULL*/)
	: CDialog(CFileDateFilterForm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileDateFilterForm)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFileDateFilterForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileDateFilterForm)
	DDX_Control(pDX, IDC_IGNORE_TIME_MODIFIED, m_IgnoreTimeModified);
	DDX_Control(pDX, IDC_IGNORE_TIME_CREATED, m_IgnoreTimeCreated);
	DDX_Control(pDX, IDC_IGNORE_TIME_ACCESSED, m_IgnoreTimeAccessed);
	DDX_Control(pDX, IDC_OPTION_MODIFIED, m_OptionModified);
	DDX_Control(pDX, IDC_OPTION_ACCESSED, m_OptionAccessed);
	DDX_Control(pDX, IDC_FILTERTYPE_MODIFIED, m_FilterTypeModified);
	DDX_Control(pDX, IDC_FILTERTYPE_ACCESSED, m_FilterTypeAccessed);
	DDX_Control(pDX, IDC_DATETIME_MODIFIED2, m_DateTimeModified2);
	DDX_Control(pDX, IDC_DATETIME_MODIFIED1, m_DateTimeModified1);
	DDX_Control(pDX, IDC_DATETIME_ACCESSED2, m_DateTimeAccessed2);
	DDX_Control(pDX, IDC_DATETIME_ACCESSED1, m_DateTimeAccessed1);
	DDX_Control(pDX, IDC_OPTION_CREATED, m_OptionCreated);
	DDX_Control(pDX, IDC_DATETIME_CREATED2, m_DateTimeCreated2);
	DDX_Control(pDX, IDC_DATETIME_CREATED1, m_DateTimeCreated1);
	DDX_Control(pDX, IDC_FILTERTYPE_CREATED, m_FilterTypeCreated);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileDateFilterForm, CDialog)
	//{{AFX_MSG_MAP(CFileDateFilterForm)
	ON_CBN_SELCHANGE(IDC_OPTION_CREATED, OnSelchangeOptionCreated)
	ON_CBN_SELCHANGE(IDC_OPTION_MODIFIED, OnSelchangeOptionModified)
	ON_CBN_SELCHANGE(IDC_OPTION_ACCESSED, OnSelchangeOptionAccessed)
	ON_CBN_SELCHANGE(IDC_FILTERTYPE_CREATED, OnSelchangeFiltertypeCreated)
	ON_CBN_SELCHANGE(IDC_FILTERTYPE_MODIFIED, OnSelchangeFiltertypeModified)
	ON_CBN_SELCHANGE(IDC_FILTERTYPE_ACCESSED, OnSelchangeFiltertypeAccessed)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileDateFilterForm message handlers




void CFileDateFilterForm::OnSelchangeOptionCreated() 
{
	bool Option = m_OptionCreated.GetCurSel() != 1;
 m_FilterTypeCreated.EnableWindow(Option);
	m_DateTimeCreated1.EnableWindow(Option);
 m_IgnoreTimeCreated.EnableWindow(Option);

	if ( Option )
	{
		OnSelchangeFiltertypeCreated();
 }
	else
	{
	 m_DateTimeCreated2.EnableWindow(Option);
  GetDlgItem(IDC_AND_CREATED)->EnableWindow(Option);
	}
}

void CFileDateFilterForm::OnSelchangeOptionModified() 
{
	bool Option = m_OptionModified.GetCurSel() != 1;
 m_FilterTypeModified.EnableWindow(Option);
	m_DateTimeModified1.EnableWindow(Option);
	m_IgnoreTimeModified.EnableWindow(Option);

	if ( Option )
	{
		OnSelchangeFiltertypeModified();
	}
	else
	{
		m_DateTimeModified2.EnableWindow(Option);
		GetDlgItem(IDC_AND_MODIFIED)->EnableWindow(Option);
	}
}

void CFileDateFilterForm::OnSelchangeOptionAccessed() 
{
	bool Option = m_OptionAccessed.GetCurSel() != 1;
 m_FilterTypeAccessed.EnableWindow(Option);
	m_DateTimeAccessed1.EnableWindow(Option);
	m_IgnoreTimeAccessed.EnableWindow(Option);

	if ( Option )
	{
		OnSelchangeFiltertypeAccessed();
	}
	else
	{
		m_DateTimeAccessed2.EnableWindow(Option);
		GetDlgItem(IDC_AND_ACCESSED)->EnableWindow(Option);
	}
}
BOOL CFileDateFilterForm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
 m_DateTimeCreated1.SetFormat(DATETIMEFORMAT);
 m_DateTimeCreated2.SetFormat(DATETIMEFORMAT);
 m_DateTimeModified1.SetFormat(DATETIMEFORMAT);
 m_DateTimeModified2.SetFormat(DATETIMEFORMAT);
 m_DateTimeAccessed1.SetFormat(DATETIMEFORMAT);
 m_DateTimeAccessed2.SetFormat(DATETIMEFORMAT);

 m_OptionCreated.SetCurSel(1);
 m_OptionModified.SetCurSel(1);
 m_OptionAccessed.SetCurSel(1);

	m_FilterTypeCreated.SetCurSel(0);
	m_FilterTypeModified.SetCurSel(0);
	m_FilterTypeAccessed.SetCurSel(0);

	OnSelchangeOptionCreated(); 
	OnSelchangeOptionModified(); 
	OnSelchangeOptionAccessed(); 

	m_IgnoreTimeCreated.SetCheck(BST_CHECKED);
	m_IgnoreTimeModified.SetCheck(BST_CHECKED);
	m_IgnoreTimeAccessed.SetCheck(BST_CHECKED);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFileDateFilterForm::OnSelchangeFiltertypeCreated() 
{
	bool Option = m_FilterTypeCreated.GetCurSel() > 3;
	m_DateTimeCreated2.EnableWindow(Option);
 GetDlgItem(IDC_AND_CREATED)->EnableWindow(Option);
}

void CFileDateFilterForm::OnSelchangeFiltertypeModified() 
{
	bool Option = m_FilterTypeModified.GetCurSel() > 3;
	m_DateTimeModified2.EnableWindow(Option);
 GetDlgItem(IDC_AND_MODIFIED)->EnableWindow(Option);
}

void CFileDateFilterForm::OnSelchangeFiltertypeAccessed() 
{
	bool Option = m_FilterTypeAccessed.GetCurSel() > 3;
	m_DateTimeAccessed2.EnableWindow(Option);
 GetDlgItem(IDC_AND_ACCESSED)->EnableWindow(Option);
}

void CFileDateFilterForm::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CFileDateFilterForm::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	//CDialog::OnCancel();
}
