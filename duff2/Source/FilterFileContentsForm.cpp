// FileContentsFilterForm.cpp : implementation file
//

#include "stdafx.h"
#include "duff.h"
#include "FilterFileContentsForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileContentsFilterForm dialog


CFileContentsFilterForm::CFileContentsFilterForm(CWnd* pParent /*=NULL*/)
	: CDialog(CFileContentsFilterForm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileContentsFilterForm)
	//}}AFX_DATA_INIT
}


void CFileContentsFilterForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileContentsFilterForm)
	DDX_Control(pDX, IDC_CONTENT_STRING, m_ContentString);
	DDX_Control(pDX, IDC_CASE_SENSITIVE, m_CaseSensitive);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileContentsFilterForm, CDialog)
	//{{AFX_MSG_MAP(CFileContentsFilterForm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileContentsFilterForm message handlers

BOOL CFileContentsFilterForm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
 CheckRadioButton(IDC_CONTAINS_DATA,IDC_DOES_NOT_CONTAIN_DATA,IDC_CONTAINS_DATA);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
