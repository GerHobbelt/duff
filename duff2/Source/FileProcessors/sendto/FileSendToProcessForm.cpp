// FileSendToProcessForm.cpp : implementation file
//

#include "stdafx.h"
#include "sendto.h"
#include "FileSendToProcessForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileSendToProcessForm dialog


CFileSendToProcessForm::CFileSendToProcessForm(CWnd* pParent /*=NULL*/)
	: CDialog(CFileSendToProcessForm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileSendToProcessForm)
	m_Program = _T("");
	m_Parameters = _T("");
	//}}AFX_DATA_INIT
}


void CFileSendToProcessForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileSendToProcessForm)
	DDX_Control(pDX, IDC_PROGRAM, m_ProgramCtrl);
	DDX_Control(pDX, IDC_PARAMETERS, m_ParametersCtrl);
	DDX_Text(pDX, IDC_PROGRAM, m_Program);
	DDV_MaxChars(pDX, m_Program, 260);
	DDX_Text(pDX, IDC_PARAMETERS, m_Parameters);
	DDV_MaxChars(pDX, m_Parameters, 260);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileSendToProcessForm, CDialog)
	//{{AFX_MSG_MAP(CFileSendToProcessForm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileSendToProcessForm message handlers

BOOL CFileSendToProcessForm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
 this->CheckRadioButton(IDC_OPTION_SEPERATE,IDC_OPTION_COMBINED,IDC_OPTION_SEPERATE	);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
