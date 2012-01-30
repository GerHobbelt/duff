// FileDeleteProcessForm.cpp : implementation file
//

#include "stdafx.h"
#include "delete.h"
#include "FileDeleteProcessForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileDeleteProcessForm dialog


CFileDeleteProcessForm::CFileDeleteProcessForm(CWnd* pParent /*=NULL*/)
	: CDialog(CFileDeleteProcessForm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileDeleteProcessForm)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFileDeleteProcessForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileDeleteProcessForm)
	DDX_Control(pDX, IDC_YES_TO_ALL, m_YesToAll);
	DDX_Control(pDX, IDC_DELETE_READONLY, m_DeleteReadOnly);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileDeleteProcessForm, CDialog)
	//{{AFX_MSG_MAP(CFileDeleteProcessForm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileDeleteProcessForm message handlers

BOOL CFileDeleteProcessForm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
CheckRadioButton(	IDC_RECYCLE,IDC_DELETE,IDC_RECYCLE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFileDeleteProcessForm::OnCancel() 
{
	// TODO: Add extra cleanup here
	
//	CDialog::OnCancel();
}

void CFileDeleteProcessForm::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}
