// FileMoveProcessForm.cpp : implementation file
//

#include "stdafx.h"
#include "move.h"
#include "FileMoveProcessForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileMoveProcessForm dialog


CFileMoveProcessForm::CFileMoveProcessForm(CWnd* pParent /*=NULL*/)
	: CDialog(CFileMoveProcessForm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileMoveProcessForm)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFileMoveProcessForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileMoveProcessForm)
	DDX_Control(pDX, IDC_MOVE_READ_ONLY, m_MoveReadOnly);
	DDX_Control(pDX, IDC_DIR, m_Dir);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileMoveProcessForm, CDialog)
	//{{AFX_MSG_MAP(CFileMoveProcessForm)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileMoveProcessForm message handlers

void CFileMoveProcessForm::OnBrowse() 
{
	m_Dir.Browse();
	/*
	CString strFolderPath;

 if( GetFolder(&strFolderPath, "Browse for folder to move files to", this->m_hWnd, NULL, NULL) )
	{
		m_Dir.SetWindowText(strFolderPath);
	}
	*/
}

void CFileMoveProcessForm::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}

void CFileMoveProcessForm::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	//CDialog::OnCancel();
}

BOOL CFileMoveProcessForm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_Dir.SetActionType( CFilenameEdit::AT_READ );
 m_Dir.SetEditType( CFilenameEdit::ET_FOLDER );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
