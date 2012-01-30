// FileSizeFilterForm.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "FilterFileSizeForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileSizeFilterForm dialog


CFileSizeFilterForm::CFileSizeFilterForm(CWnd* pParent /*=NULL*/)
	: CDialog(CFileSizeFilterForm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileSizeFilterForm)
	m_FilterType = 0;
	m_Value1 = 0;
	m_Value2 = 0;
	//}}AFX_DATA_INIT
}


void CFileSizeFilterForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileSizeFilterForm)
	DDX_Control(pDX, IDC_VALUE2, m_Value2Control);
	DDX_Control(pDX, IDC_VALUE1, m_Value1Control);
	DDX_Control(pDX, IDC_FILTER_TYPE, m_FilterTypeControl);
	DDX_CBIndex(pDX, IDC_FILTER_TYPE, m_FilterType);
	DDX_Text(pDX, IDC_VALUE1, m_Value1);
	DDV_MinMaxDWord(pDX, m_Value1, 0, 4294967295);
	DDX_Text(pDX, IDC_VALUE2, m_Value2);
	DDV_MinMaxDWord(pDX, m_Value2, 0, 4294967295);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileSizeFilterForm, CDialog)
	//{{AFX_MSG_MAP(CFileSizeFilterForm)
	ON_CBN_EDITCHANGE(IDC_FILTER_TYPE, OnEditchangeFilterType)
	ON_CBN_SELCHANGE(IDC_FILTER_TYPE, OnSelchangeFilterType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileSizeFilterForm message handlers

void CFileSizeFilterForm::OnEditchangeFilterType() 
{
 
}

void CFileSizeFilterForm::OnSelchangeFilterType() 
{

/*
0 Not equal to
1 Equal to
2 Greater than
3 Less than
4 Between
5 Not between
*/
 int FilterType = m_FilterTypeControl.GetCurSel();

	GetDlgItem(IDC_STATIC_AND)->EnableWindow(FilterType == 4 || FilterType == 5);
	GetDlgItem(IDC_VALUE2)->EnableWindow(FilterType == 4 || FilterType == 5);


}

BOOL CFileSizeFilterForm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
OnSelchangeFilterType() ;	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CFileSizeFilterForm::OnCancel() 
{
	// TODO: Add extra cleanup here
	
//	CDialog::OnCancel();
}

void CFileSizeFilterForm::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}
