// FileSaveListProcessForm.cpp : implementation file
//

#include "stdafx.h"
#include "savelist.h"
#include "FileSaveListProcessForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileSaveListProcessForm dialog


CFileSaveListProcessForm::CFileSaveListProcessForm(CWnd* pParent /*=NULL*/)
	: CDialog(CFileSaveListProcessForm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileSaveListProcessForm)
	//}}AFX_DATA_INIT
}


void CFileSaveListProcessForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileSaveListProcessForm)
	DDX_Control(pDX, IDC_NEWLINE, m_NewLine);
	DDX_Control(pDX, IDC_LINE_FORMAT, m_LineFormat);
	DDX_Control(pDX, IDC_FILENAME, m_Filename);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileSaveListProcessForm, CDialog)
	//{{AFX_MSG_MAP(CFileSaveListProcessForm)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileSaveListProcessForm message handlers

void CFileSaveListProcessForm::OnBrowse() 
{
 CFileDialog dlg(FALSE, "txt",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"Text files (*.txt)|*.txt|All Files (*.*)|*.*|",this);
	if ( dlg.DoModal() == IDOK )
	{
  m_Filename.SetWindowText( dlg.GetPathName() );
		UpdateData(FALSE);
	}

}


void CFileSaveListProcessForm::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CFileSaveListProcessForm::OnCancel() 
{
	// TODO: Add extra cleanup here
	
//	CDialog::OnCancel();
}
